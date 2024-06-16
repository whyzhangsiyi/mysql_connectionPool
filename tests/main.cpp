
#include <../include/MysqlConnection.hpp>
#include <../include/connectionPool.hpp>
#include <../include/threadSafeQueue.hpp>
#include <../mysqlConn/include/prepared_statement.h>
#include <iostream>
#include <atomic>

sql::Driver *driver = get_driver_instance();

connectionPool *pool = connectionPool::getConnectionPoolInstance();

threadSafeQueue<std::shared_ptr<MysqlConnection>> Q;

int counter = 200000;
int threadNum=8;

// !!!每次测试只能开启一个测试选项

#define noPoolWithSingleThread 0

#define poolWtihSingleThread 0


#define noPoolWithMutiThread 0

#define poolWithMutiThread 0



#if poolWithMutiThread | noPoolWithMutiThread

void pressTest1()
{
#if poolWithMutiThread
    for (size_t i = 0; i < counter / threadNum; i++)
    {
        std::shared_ptr<MysqlConnection> conn = pool->getConnection();
        if (conn != nullptr)
        {
            sql::Connection *handler = conn->getConnectionHandler();
            sql::PreparedStatement *preSta = handler->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
            preSta->setString(1, std::string("张a") + std::to_string(i));
            preSta->setInt(2, 43);
            preSta->setString(3, "M");
            preSta->execute();
            preSta->close();
            delete preSta;
        }
        else
        {
            i--;
        }
    }
#endif

#if noPoolWithMutiThread

    for (size_t i = 0; i < counter / threadNum; i++) // 不使用连接池
    {
        sql::Connection *conn = driver->connect("tcp://172.16.235.134:3306", "ziggy", "\/\///");
        conn->setSchema("school");
        sql::PreparedStatement *preSta = conn->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
        preSta->setString(1, std::string("李四a") + std::to_string(i));
        preSta->setInt(2, 45);
        preSta->setString(3, "M");
        preSta->execute();
        preSta->close();
        conn->close();
        delete preSta;
        delete conn;
    }
    #endif 
}

void pressTest2()
{
#if poolWithMutiThread
    for (size_t i = 0; i < counter / threadNum; i++)
    {
        std::shared_ptr<MysqlConnection> conn = pool->getConnection();
        if (conn != nullptr)
        {
            sql::Connection *handler = conn->getConnectionHandler();
            sql::PreparedStatement *preSta = handler->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
            preSta->setString(1, std::string("张b") + std::to_string(i));
            preSta->setInt(2, 43);
            preSta->setString(3, "M");
            preSta->execute();
            preSta->close();
            delete preSta;
        }
        else
        {
            i--;
        }
    }
#endif

#if noPoolWithMutiThread

    for (size_t i = 0; i < counter / threadNum; i++) // 不使用连接池
    {
        sql::Connection *conn = driver->connect("tcp://172.16.235.134:3306", "ziggy", "\/\///");
        conn->setSchema("school");
        sql::PreparedStatement *preSta = conn->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
        preSta->setString(1, std::string("李四b") + std::to_string(i));
        preSta->setInt(2, 45);
        preSta->setString(3, "M");
        preSta->execute();
        preSta->close();
        conn->close();
        delete preSta;
        delete conn;
    }
#endif
}
void pressTest3()
{
#if poolWithMutiThread
    for (size_t i = 0; i < counter / threadNum; i++)
    {
        std::shared_ptr<MysqlConnection> conn = pool->getConnection();
        if (conn != nullptr)
        {
            sql::Connection *handler = conn->getConnectionHandler();
            sql::PreparedStatement *preSta = handler->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
            preSta->setString(1, std::string("张c") + std::to_string(i));
            preSta->setInt(2, 43);
            preSta->setString(3, "M");
            preSta->execute();
            preSta->close();
            delete preSta;
        }
        else
        {
            i--;
        }
    }
#endif

#if noPoolWithMutiThread

    for (size_t i = 0; i < counter / threadNum; i++) // 不使用连接池
    {
        sql::Connection *conn = driver->connect("tcp://172.16.235.134:3306", "ziggy", "\/\///");
        conn->setSchema("school");
        sql::PreparedStatement *preSta = conn->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
        preSta->setString(1, std::string("李四c") + std::to_string(i));
        preSta->setInt(2, 45);
        preSta->setString(3, "M");
        preSta->execute();
        preSta->close();
        conn->close();
        delete preSta;
        delete conn;
    }
#endif
}
void pressTest4()
{
#if poolWithMutiThread
    for (size_t i = 0; i < counter / threadNum; i++)
    {
        std::shared_ptr<MysqlConnection> conn = pool->getConnection();
        if (conn != nullptr)
        {
            sql::Connection *handler = conn->getConnectionHandler();
            sql::PreparedStatement *preSta = handler->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
            preSta->setString(1, std::string("张d") + std::to_string(i));
            preSta->setInt(2, 43);
            preSta->setString(3, "M");
            preSta->execute();
            preSta->close();
            delete preSta;
        }
        else
        {
            i--;
        }
    }
#endif

#if noPoolWithMutiThread

    for (size_t i = 0; i < counter / threadNum; i++) // 不使用连接池
    {
        sql::Connection *conn = driver->connect("tcp://172.16.235.134:3306", "ziggy", "\/\///");
        conn->setSchema("school");
        sql::PreparedStatement *preSta = conn->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
        preSta->setString(1, std::string("李四d") + std::to_string(i));
        preSta->setInt(2, 45);
        preSta->setString(3, "M");
        preSta->execute();
        preSta->close();
        conn->close();
        delete preSta;
        delete conn;
    }
#endif
}

void pressTest5()
{
#if poolWithMutiThread
    for (size_t i = 0; i < counter / threadNum; i++)
    {
        std::shared_ptr<MysqlConnection> conn = pool->getConnection();
        if (conn != nullptr)
        {
            sql::Connection *handler = conn->getConnectionHandler();
            sql::PreparedStatement *preSta = handler->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
            preSta->setString(1, std::string("张g") + std::to_string(i));
            preSta->setInt(2, 43);
            preSta->setString(3, "M");
            preSta->execute();
            preSta->close();
            delete preSta;
        }
        else
        {
            i--;
        }
    }
#endif

#if noPoolWithMutiThread

    for (size_t i = 0; i < counter / threadNum; i++) // 不使用连接池
    {
        sql::Connection *conn = driver->connect("tcp://172.16.235.134:3306", "ziggy", "\/\///");
        conn->setSchema("school");
        sql::PreparedStatement *preSta = conn->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
        preSta->setString(1, std::string("李四e") + std::to_string(i));
        preSta->setInt(2, 45);
        preSta->setString(3, "M");
        preSta->execute();
        preSta->close();
        conn->close();
        delete preSta;
        delete conn;
    }
#endif
}

void pressTest6()
{
#if poolWithMutiThread
    for (size_t i = 0; i < counter / threadNum; i++)
    {
        std::shared_ptr<MysqlConnection> conn = pool->getConnection();
        if (conn != nullptr)
        {
            sql::Connection *handler = conn->getConnectionHandler();
            sql::PreparedStatement *preSta = handler->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
            preSta->setString(1, std::string("张k") + std::to_string(i));
            preSta->setInt(2, 43);
            preSta->setString(3, "M");
            preSta->execute();
            preSta->close();
            delete preSta;
        }
        else
        {
            i--;
        }
    }
#endif

#if noPoolWithMutiThread

    for (size_t i = 0; i < counter / threadNum; i++) // 不使用连接池
    {
        sql::Connection *conn = driver->connect("tcp://172.16.235.134:3306", "ziggy", "\/\///");
        conn->setSchema("school");
        sql::PreparedStatement *preSta = conn->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
        preSta->setString(1, std::string("李四f") + std::to_string(i));
        preSta->setInt(2, 45);
        preSta->setString(3, "M");
        preSta->execute();
        preSta->close();
        conn->close();
        delete preSta;
        delete conn;
    }
#endif
}

void pressTest7()
{
#if poolWithMutiThread
    for (size_t i = 0; i < counter / threadNum; i++)
    {
        std::shared_ptr<MysqlConnection> conn = pool->getConnection();
        if (conn != nullptr)
        {
            sql::Connection *handler = conn->getConnectionHandler();
            sql::PreparedStatement *preSta = handler->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
            preSta->setString(1, std::string("张r") + std::to_string(i));
            preSta->setInt(2, 43);
            preSta->setString(3, "M");
            preSta->execute();
            preSta->close();
            delete preSta;
        }
        else
        {
            i--;
        }
    }
#endif

#if noPoolWithMutiThread

    for (size_t i = 0; i < counter / threadNum; i++) // 不使用连接池
    {
        sql::Connection *conn = driver->connect("tcp://172.16.235.134:3306", "ziggy", "\/\///");
        conn->setSchema("school");
        sql::PreparedStatement *preSta = conn->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
        preSta->setString(1, std::string("李四g") + std::to_string(i));
        preSta->setInt(2, 45);
        preSta->setString(3, "M");
        preSta->execute();
        preSta->close();
        conn->close();
        delete preSta;
        delete conn;
    }
#endif
}

void pressTest8()
{

#if poolWithMutiThread
    for (size_t i = 0; i < counter / threadNum; i++)
    {
        std::shared_ptr<MysqlConnection> conn = pool->getConnection();
        if (conn != nullptr)
        {
            sql::Connection *handler = conn->getConnectionHandler();
            sql::PreparedStatement *preSta = handler->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
            preSta->setString(1, std::string("张p") + std::to_string(i));
            preSta->setInt(2, 43);
            preSta->setString(3, "M");
            preSta->execute();
            preSta->close();
            delete preSta;
        }
        else
        {
            i--;
        }
    }
#endif

#if noPoolWithMutiThread

    for (size_t i = 0; i < counter / threadNum; i++) // 不使用连接池
    {
        sql::Connection *conn = driver->connect("tcp://172.16.235.134:3306", "ziggy", "\/\///");
        conn->setSchema("school");
        sql::PreparedStatement *preSta = conn->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
        preSta->setString(1, std::string("李四h") + std::to_string(i));
        preSta->setInt(2, 45);
        preSta->setString(3, "M");
        preSta->execute();
        preSta->close();
        conn->close();
        delete preSta;
        delete conn;
    }
#endif
}

#endif

int main()
{

    std::chrono::time_point<std::chrono::system_clock> c1 = std::chrono::system_clock::now();

#if poolWithMutiThread | noPoolWithMutiThread

    std::thread t1(pressTest1);
    std::thread t2(pressTest2);
    std::thread t3(pressTest3);
    std::thread t4(pressTest4);
    std::thread t5(pressTest5);
    std::thread t6(pressTest6);
    std::thread t7(pressTest7);
    std::thread t8(pressTest8);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();


#endif

#if poolWtihSingleThread
 
    for (size_t i = 0; i < counter ; i++)
    {
        std::shared_ptr<MysqlConnection> conn = pool->getConnection();
        if (conn != nullptr)
        {
            sql::Connection *handler = conn->getConnectionHandler();
            sql::PreparedStatement *preSta = handler->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
            preSta->setString(1, std::string("张q") + std::to_string(i));
            preSta->setInt(2, 43);
            preSta->setString(3, "M");
            preSta->execute();
            preSta->close();
            delete preSta;
        }
        else
        {
            i--;
        }
    }

#endif

#if noPoolWithSingleThread

    for (size_t i = 0; i < counter; i++)         //不使用连接池
    {
        sql::Connection *conn = driver->connect("tcp://172.16.235.134:3306","ziggy","\/\///");
        conn->setSchema("school");
        sql::PreparedStatement *preSta = conn->prepareStatement("insert into user(name,age,sex) values(?,?,?)");
        preSta->setString(1, std::string("李四") + std::to_string(i));
        preSta->setInt(2,45);
        preSta->setString(3, "M");
        preSta->execute();
        preSta->close();
        conn->close();
        delete preSta;
        delete conn;
    }

#endif



    std::chrono::time_point<std::chrono::system_clock> c2 = std::chrono::system_clock::now();

    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(c2 - c1);



#if noPoolWithSingleThread

    std::cout << "单线程不使用连接池获取" << counter << "个连接耗时: " << time1.count() / 1000.0 << "s" << std::endl;

#endif

#if poolWtihSingleThread

    std::cout << "单线程使用连接池获取" << counter << "个连接耗时: " << time1.count() / 1000.0 << "s" << std::endl;

#endif

#if noPoolWithMutiThread

    std::cout << "多线程使用不使用连接池获取" << counter << "个连接耗时: " << time1.count() / 1000.0 << "s" << std::endl;
#endif


#if poolWithMutiThread

    std::cout << "多线程使用连接池获取" << counter << "个连接耗时: " << time1.count() / 1000.0 << "s" << std::endl;
#endif



    return 0;
}
