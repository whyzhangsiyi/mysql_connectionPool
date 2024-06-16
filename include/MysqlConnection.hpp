#pragma once
#include <../mysqlConn/include/driver.h>
#include <../mysqlConn/include/connection.h>
#include <../mysqlConn/include/statement.h>
#include <../mysqlConn/include/resultset.h>
#include <../mysqlConn/include/exception.h>
#include <memory> // For std::shared_ptr
#include <chrono>

// using time_point_t = std::chrono::time_point<std::chrono::system_clock>;
// 
// typedef std::chrono::time_point<std::chrono::system_clock> time_point_t;

class MysqlConnection
{

    friend class connectionPool;
private:
    static sql::Driver *_mysqlConnDriver;
    sql::Connection *_Conn;
    std::chrono::time_point<std::chrono::system_clock> _timePoint;

    private:
        std::chrono::time_point<std::chrono::system_clock> getTimePoint();
        void setTimePoint(std::chrono::time_point<std::chrono::system_clock> tp);
        void flushTimePoint();
        std::chrono::milliseconds getIdleDuration();

    public:
        MysqlConnection(std::string ipPort, std::string user, std::string password);
       
        MysqlConnection(){

            _Conn=nullptr;
            
        }

        ~MysqlConnection();

        sql::Connection *getConnectionHandler();
    
};
