#include "ThreadPool.h"

/**
 * Constructs a thread pool with the specified number of threads.
 * @param threads The number of worker threads in the pool.
 */
ThreadPool::ThreadPool(size_t threads)
        : stop(false) { // Initializes the 'stop' flag to false
    for (size_t i = 0; i < threads; ++i) {
        // Each worker thread executes this lambda function
        workers.emplace_back(
                [this] {
                    while (true) { // Worker threads run indefinitely until 'stop' is set to true
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);
                            // Wait until there is a task in the queue or the pool is stopped
                            this->condition.wait(lock,
                                                 [this] { return this->stop || !this->tasks.empty(); });
                            // If stop is true and tasks are empty, exit the thread
                            if (this->stop && this->tasks.empty())
                                return;
                            // Retrieve the next task from the queue
                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }
                        // Execute the task
                        task();
                    }
                }
        );
    }
}

/**
 * Destructor for the ThreadPool class. Stops all worker threads before exiting.
 */
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        // Set 'stop' flag to true to signal all threads to stop
        stop = true;
    }
    // Notify all waiting threads
    condition.notify_all();
    // Join all threads to ensure they complete execution
    for (std::thread &worker: workers)
        worker.join();
}

/**
 * Enqueues a task to be executed by the thread pool.
 * @param task The task (function) to be executed.
 */
void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        // Check if adding tasks is allowed (thread pool has not been stopped)
        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");
        // Add the task to the queue
        tasks.emplace(task);
    }
    // Notify one waiting thread that a new task is available
    condition.notify_one();
}


