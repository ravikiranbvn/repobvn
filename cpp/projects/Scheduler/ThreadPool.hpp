#pragma once

#include <future>
#include <functional>
#include <thread>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <iostream>

template<typename F, typename... Args>
using JobReturnType = typename std::result_of<F(Args...)>::type;

enum class Priority : size_t
{
   Normal,
   High,
   Critical
};

class ThreadPool
{
public:
       ThreadPool(size_t threadCount = std::thread::hardware_concurrency());	
       ThreadPool(ThreadPool&&) = default;
       ThreadPool& operator=(ThreadPool&&) = default;
	
       ~ThreadPool();
       ThreadPool(const ThreadPool&) = delete;
       ThreadPool& operator=(const ThreadPool&) = delete;
       	
       template <typename F, typename... Args>
       auto startWithPriority(Priority priority, F&& f, Args&&... args) -> std::future<JobReturnType<F, Args...>>
       {
          auto job = std::make_shared<std::packaged_task<JobReturnType<F, Args...>()>>
			(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

	   addTask(priority, [job] { (*job)();});
	   return job->get_future();
       }
       
       template <typename F, typename... Args>
       auto start(F&& f, Args&&... args) -> std::future<JobReturnType<F, Args...>>
       {
	    return startWithPriority(Priority::Normal, std::forward<F>(f), std::forward<Args>(args)...);
       }

       void shutDown();

private:
       void initialize(size_t threadCount);	
       void addTask(Priority priority, std::function<void()> job);
       void handlerTask();

       std::mutex m_mutex;
       std::condition_variable m_cv;
       std::vector<std::thread> m_workers;
       std::map<Priority, std::queue<std::function<void()>>, std::greater<Priority>> m_tasksByPriority;
};
