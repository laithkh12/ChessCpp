//
// Created by leth1 on 7/14/2024.
//

#ifndef CHESS_THREADPOOL_H
#define CHESS_THREADPOOL_H
#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t threads);
    ~ThreadPool();

    template<class F>
    void enqueue(F&& f);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

ThreadPool::ThreadPool(size_t threads) : stop(false) {
    for(size_t i = 0; i < threads; ++i) {
        workers.emplace_back(
                [this] {
                    for(;;) {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            this->condition.wait(lock,
                                                 [this]{ return this->stop.load() || !this->tasks.empty(); });
                            if(this->stop.load() && this->tasks.empty())
                                return;
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }

                        task();
                    }
                }
        );
    }
}

ThreadPool::~ThreadPool() {
    stop.store(true);
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}

template<class F>
void ThreadPool::enqueue(F&& f) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(stop.load())
            throw std::runtime_error("enqueue on stopped ThreadPool");
        tasks.emplace(std::forward<F>(f));
    }
    condition.notify_one();
}


#endif //CHESS_THREADPOOL_H