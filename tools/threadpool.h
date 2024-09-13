#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool {
public:
    ThreadPool(size_t t) {
        for (size_t i = 0; i < t; ++i) {

        }
    }

    template<typename Func, typename... Args>
    void enQueue(Func &&f, Args &&...args) {
        using return_type = typename std::result_of<Func(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<Func>(f),
                std::forward<Args>(args)...));
        std::future<return_type> res = task->get_future();


    }

private:
    bool stop;
    std::condition_variable cv;
    std::mutex mutex;
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> workers;
};
#endif
