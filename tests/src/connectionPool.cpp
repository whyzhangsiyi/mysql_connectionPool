#include <../include/connectionPool.hpp>

connectionPool *connectionPool::getConnectionPoolInstance()
{

    static connectionPool *singlePool = new connectionPool("/home/ziggy/workspace/mysql_connectionPool/src/cpool.conf");
    return singlePool;
}

std::shared_ptr<MysqlConnection> connectionPool::getConnection()
{


    std::unique_lock<std::mutex> uk(_mt);
    if (_cv.wait_for(uk, _connTimeOut, [this]()
                     { return !this->_que.empty(); }))
    { // 非空返回

        auto deleter = [&](MysqlConnection *conn)
        {
            std::lock_guard<std::mutex> lk(this->_mt);
            conn->flushTimePoint();
            _que.push(conn);
        };

        std::shared_ptr<MysqlConnection> conn(_que.front(), deleter);
        _que.pop();
        if (_que.empty())
        {
            _cv.notify_all();
        }

        return conn;
    }
    // 超时返回
    _cv.notify_all();                          // 提醒生产者线程
    std::cout<<"timeOut!"<<std::endl;
    return std::shared_ptr<MysqlConnection>(); // 返回空连接
}

void connectionPool::doConfig(std::string ConfFilePath)
{

    // 加载配置文件
    _fs.open(ConfFilePath);
    try
    {
        if (!_fs.is_open())
        {
            std::cout << "配置文件打开失败" << std::endl;
            throw("配置文件打开失败!");
        }
        std::map<std::string, Conf> ConfMap;
        // 配置项
        ConfMap.insert({"#", Conf::COMMENT});
        ConfMap.insert({"ip_port", Conf::IP_PORT});
        ConfMap.insert({"username", Conf::USERNAME});
        ConfMap.insert({"password", Conf::PASSWORD});
        ConfMap.insert({"dbname", Conf::DBNAME});
        ConfMap.insert({"initSize", Conf::INITSIZE});
        ConfMap.insert({"maxSize", Conf::MAXSIZE});
        ConfMap.insert({"maxIdleTime", Conf::MAXIDLETIME});
        ConfMap.insert({"connTimeOut", Conf::CONNTIMEOUT});

        std::string ConfLine;

        while (std::getline(_fs, ConfLine))
        {
            std::cerr << "读取配置文件" << std::endl;

            std::stringstream ssm(ConfLine);
            std::string conf;
            std::string dilimiter;
            std::string value;
            if (ConfLine.at(0) == '#')
            {
                continue;
            }
            else // 非注释行,读配置项与值
            {
                ssm >> conf;
                ssm >> dilimiter;
                ssm >> value;
                if (dilimiter != "=")
                {
                    throw("配置文件格式错误");
                }
            }

            Conf ConfItem = ConfMap.at(conf); // 使用字符串转换成枚举进行 switch
            switch (ConfItem)
            {

            case Conf::IP_PORT:
                _ipPort = value;
                break;
            case Conf::USERNAME:
                _userName = value;
                break;
            case Conf::PASSWORD:
                _password = value;
                break;
            case Conf::DBNAME:
                _dbName = value;
                break;
            case Conf::INITSIZE:
                _initSize = std::stoi(value);
                break;
            case Conf::MAXSIZE:
                _maxSize = std::stoi(value);
                break;
            case Conf::MAXIDLETIME:
                _maxIdleTime = std::chrono::milliseconds(std::stoi(value));
                break;
            case Conf::CONNTIMEOUT:
                _connTimeOut = std::chrono::milliseconds(std::stoi(value));
                break;
            default:
                break;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        _fs.close();
        exit(1);
    }

    _fs.close();
}

void connectionPool::doQueInit()
{

    std::lock_guard<std::mutex> lk(_mt);
    for (size_t i = 0; i < _initSize; i++)
    {
        MysqlConnection *newConn = new MysqlConnection(_ipPort, _userName, _password);
        newConn->flushTimePoint();
        newConn->getConnectionHandler()->setSchema(_dbName);
        _que.push(newConn);
        _connCounter++;
    }

}

void connectionPool::doExpand()
{

    while (!_readyFlag)
    {
        ;
    }

    while (true)
    {
        std::unique_lock<std::mutex> uk(_mt);
        _cv.wait(uk, [this]()
                 { return this->_que.empty(); });
        if (_connCounter >= _maxSize)
        {
            continue;
        }

        MysqlConnection *newConn = new MysqlConnection(_ipPort, _userName, _password);
        newConn->flushTimePoint();
        newConn->getConnectionHandler()->setSchema(_dbName);
        _que.push(newConn);
        _connCounter++;
        _cv.notify_all();
    }
}

void connectionPool::doShrink()
{

    while (!_readyFlag)
    {
        ;
    }

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(_maxIdleTime.count()));
        std::lock_guard<std::mutex> lock(_mt);
        while (!_que.empty())
        {

            if ((_que.front()->getIdleDuration() > _maxIdleTime) && (_connCounter > _initSize))
            {
                MysqlConnection *conn = _que.front();
                _que.pop();
                _connCounter--;
                delete conn;
            }
            else
            {
                break;
            }
        }
    }
}

connectionPool::connectionPool(std::string ConfFilePath) : _readyFlag(false),
                                                           _connCounter(0),
                                                           _initSize(256), // 连接池的默认配置
                                                           _maxSize(1024),
                                                           _maxIdleTime(5000),
                                                           _connTimeOut(1000),
                                                           _expandThead(std::bind(&connectionPool::doExpand, this)),
                                                           _shrinkThread(std::bind(&connectionPool::doShrink, this))
{

    doConfig(ConfFilePath);
    doQueInit();
    _readyFlag = true;
    _expandThead.detach();
    _shrinkThread.detach();
}

connectionPool::~connectionPool()
{
}
