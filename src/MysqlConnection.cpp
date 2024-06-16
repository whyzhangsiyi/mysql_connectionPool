#include <../include/MysqlConnection.hpp>

// 初始化驱动器
sql::Driver *MysqlConnection::_mysqlConnDriver = get_driver_instance();
//********************构造,析构函数
MysqlConnection::~MysqlConnection()
{
    _Conn->close();
}

MysqlConnection::MysqlConnection(std::string ipPort, std::string user, std::string password)
{
    
    _Conn = _mysqlConnDriver->connect(ipPort, user, password);
    _timePoint = std::chrono::system_clock::now();
}
//************************

std::chrono::time_point<std::chrono::system_clock> MysqlConnection::getTimePoint()
{
    return _timePoint;
}

void MysqlConnection::setTimePoint(std::chrono::time_point<std::chrono::system_clock> tp)
{

    _timePoint = tp;
    
}

std::chrono::milliseconds MysqlConnection::getIdleDuration()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - (_timePoint));
}

void MysqlConnection::flushTimePoint()
{
    _timePoint = std::chrono::system_clock::now();
}

sql::Connection *MysqlConnection::getConnectionHandler()
{
    return _Conn;
}
