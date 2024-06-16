#pragma once

#include <MysqlConnection.hpp>
#include <memory>
#include <map>
#include <public.hpp>
#include <fstream>
#include <sstream>
#include <thread>
#include<condition_variable>
#include<queue>


class connectionPool
{
private:

    std::queue<MysqlConnection*> _que;
    std::thread _expandThead;
    std::thread _shrinkThread;
    std::mutex _mt;
    std::condition_variable _cv;
    std::ifstream _fs;
    std::string _ipPort;
    std::string _userName;
    std::string _password;
    std::string _dbName;
    int _initSize;
    int _maxSize;
    bool _readyFlag;
    size_t _connCounter;
    std::chrono::milliseconds _maxIdleTime;
    std::chrono::milliseconds _connTimeOut;

private:
    connectionPool(std::string ConfFilePath);
    void doConfig(std::string ConfFilePath);
    void doQueInit();
    void doExpand();
    void doShrink();

public:
    std::shared_ptr<MysqlConnection> getConnection();
    size_t getPoolSize(){

        std::lock_guard<std::mutex> lk(_mt);
        return _que.size();
        
    }
    void getInfo(){
        std::cout << "ip_port-->" << _ipPort << std::endl;
        std::cout<<"username-->"<<_userName<<std::endl;
        std::cout << "password-->" << _password << std::endl;
        std::cout << "dbname-->" << _dbName << std::endl;
        std::cout<<"initSize-->"<<_initSize<<std::endl;
        std::cout << "maxSize-->" << _maxSize << std::endl;
        std::cout << "maxIdleTime-->"<< _maxIdleTime.count() << std::endl;
        std::cout << "connTimeOut-->"<< _connTimeOut.count() << std::endl;
    }
    size_t getConnCounter(){

    return _connCounter;
    }
    static connectionPool* getConnectionPoolInstance();
    ~connectionPool();
};

