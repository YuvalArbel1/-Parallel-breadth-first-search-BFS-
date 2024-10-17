#ifndef EX2_CODE_THREADPOOL_H
#define EX2_CODE_THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

/**
 * A ThreadPool class that manages a set of worker threads to execute tasks concurrently.
 */
class ThreadPool {
public:
    /**
    * Constructs a ThreadPool with a specified number of threads.
    * @param threads The number of threads in the ThreadPool.
    */
    ThreadPool(size_t threads);

    /**
     * Destructor for ThreadPool. Ensures all threads complete their tasks and stop before exiting.
     */
    ~ThreadPool();

    /**
     * Adds a new task to the ThreadPool for execution.
     * @param task A std::function representing the task to be executed.
     *             The task should be a function or callable object that takes no parameters and returns void.
     */
    void enqueue(std::function<void()> task);

private:
    // A vector of worker threads
    std::vector<std::thread> workers;
    // A queue of tasks to be executed by the worker threads
    std::queue<std::function<void()>> tasks;

    // Mutex to synchronize access to the task queue
    std::mutex queue_mutex;
    // Condition variable used for notifying worker threads
    std::condition_variable condition;
    // A flag indicating whether the ThreadPool is stopping
    bool stop;
};


#endif //EX2_CODE_THREADPOOL_H
