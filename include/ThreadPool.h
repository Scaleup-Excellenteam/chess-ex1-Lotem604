#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <utility>

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads);

    template <typename F>
    void enqueueTask(F&& task) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            if (stop) throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.push(std::function<void()>(std::forward<F>(task)));
        }
        condition.notify_one();
    }

    ~ThreadPool();

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};
