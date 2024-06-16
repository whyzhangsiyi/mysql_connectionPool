#ifndef THREADSAFEQUEUE_HPP
#define THREADSAFEQUEUE_HPP

#include <mutex>
#include <queue>
#include <condition_variable>

/*

基于生产者-消费者模型的线程安全队列
作为连接池的底层数据结构
*/

template <typename T>
class threadSafeQueue
{
private:
    std::queue<T> _que; // 用stl 的容器做适配器
    std::mutex _mt;
    std::condition_variable _cv;

public:
    threadSafeQueue();
    ~threadSafeQueue();

    bool isEmpty();
    size_t size();
    T pop();
    bool try_pop(T &val);
    bool try_pop_withOutTime(T &val, std::chrono::milliseconds ms);
    void add(T val);
    T front();
};

template <typename T>
threadSafeQueue<T>::threadSafeQueue() {}


template <typename T>
threadSafeQueue<T>::~threadSafeQueue() {}

template <typename T>
bool threadSafeQueue<T>::isEmpty()
{
    std::lock_guard<std::mutex> lock(_mt);
    return _que.empty();
}

template <typename T>
size_t threadSafeQueue<T>::size()
{
    std::lock_guard<std::mutex> lock(_mt);
    return _que.size();
}

template <typename T>
T threadSafeQueue<T>::pop()
{
    std::unique_lock<std::mutex> uk(_mt);
    _cv.wait(uk, [this]()
             { return (!this->_que.empty()); }); // 不空就唤醒返回
    T val = _que.front();
    _que.pop();
    _cv.notify_all();
    return val;
}

template <typename T>
bool threadSafeQueue<T>::try_pop(T &val)
{
    std::lock_guard<std::mutex> lock(_mt);
    if (_que.empty())
    {
        return false;
    }

    val = _que.front();
    _que.pop();
    _cv.notify_all();
    return true;
}

template <typename T>
bool threadSafeQueue<T>::try_pop_withOutTime(T &val, std::chrono::milliseconds ms)
{
    std::unique_lock<std::mutex> uk(_mt);
    if (_cv.wait_for(uk, ms, [this]()
                     { return (!this->_que.empty()); })) // 非空唤醒
    // the return of wait_for : The latest result of pred() before returning to the caller.
    {
        val = _que.front();
        _que.pop();
        _cv.notify_all();
        return true;
    }
    return false;
}

template <typename T>
void threadSafeQueue<T>::add(T val)
{
    std::lock_guard<std::mutex> lock(_mt);
    _que.push(val);
    _cv.notify_all();
}

template <typename T>
T threadSafeQueue<T>::front()
{
    std::lock_guard<std::mutex> lock(_mt);
    if (!_que.empty())
    {
        return _que.front();
    }
    return T();
}

#endif