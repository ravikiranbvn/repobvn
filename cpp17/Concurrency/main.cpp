#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "thread_pool.h"
#include <thread>

using namespace std::chrono_literals;
using namespace std;
using namespace std::literals::chrono_literals;

void checkHealthSensorCritical() 
{
   cout << "critical priority task" << "\n";
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void checkHealthSensorHigh()
{
  cout << "high priority task" << "\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void checkHealthSensorNormal()
{
  cout << "normal priority task" << "\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main()
{
	CTP::ThreadPool thread_pool;
        const auto start = std::chrono::steady_clock::now();
	
	while(1) {
        auto now = std::chrono::steady_clock::now();
	thread_pool.Schedule(CTP::Priority::Normal, &checkHealthSensorNormal);
	thread_pool.Schedule(CTP::Priority::High, &checkHealthSensorHigh);
	thread_pool.Schedule(CTP::Priority::Critical, &checkHealthSensorCritical);
	
	if(std::chrono::duration_cast<std::chrono::seconds>(now - start) >= 10s) {
	  break;
	}
	
	}
	
	return 0;
}


#include "thread_pool.h"

namespace CTP
{	
	ThreadPool::ThreadPool(size_t threadCount)
	{
		Init(threadCount);
	}

	ThreadPool::~ThreadPool()
	{
		Shutdown();
	}

	void ThreadPool::AddJob(std::function<void()>&& job, Priority priority)
	{
		std::unique_lock<std::mutex> ul(m_guard);
		m_jobsByPriority[priority].emplace(std::move(job));
		m_cvSleepCtrl.notify_one();
	}
	
	void ThreadPool::Init(size_t threadCount)
	{
		// First we explicitly initialize the 3 queues
		m_jobsByPriority[Priority::Normal] = {};
		m_jobsByPriority[Priority::High] = {};
		m_jobsByPriority[Priority::Critical] = {};

		// now explicitly reserve for the vector of threads the exact number of threads whished
		m_workers.reserve(threadCount);

		// this is where each thread is created to consume jobs from the queues
		// if we have e.g. only normal jobs - and as we have multiple threads - then 
		// we shall lock when a job is added and when a job is extracted to avoid race conditions
		for (int i = 0; i < threadCount; i++)
		{
			m_workers.push_back(std::thread([this](){

					std::function<void()> job;           
					{  
						std::unique_lock<std::mutex> ul(m_guard);
				      
						m_cvSleepCtrl.wait(ul, [this](){


							bool allQueuesEmpty = true;
							for (const auto& kvp : m_jobsByPriority)
							{
								allQueuesEmpty &= kvp.second.empty();
							}
							return !allQueuesEmpty;
						});

						for (auto& kvp : m_jobsByPriority)
						{
							auto& jobs = kvp.second; // we take here the Queue based on the Priority
							if (jobs.empty())		// if the current Queue is empty - we go the next Queue
							{
								continue;
							}
							job = std::move(jobs.front()); // once we know the current queue has a job we move it
							jobs.pop();						// and we pop one element from this Queue
							break;		
						}
					}

					if (job != nullptr)
					{
						job();
					}
				
			}));
		}
	}

	void ThreadPool::Shutdown()
	{
		// now notify all threads (effectively waking them up) so that they either execute their last job 
		// and/or directly stop working as the main flag is false
		m_cvSleepCtrl.notify_all();

		// finally join all threads to ensure all of them are waited to finish before destroying the thread pool
		for (auto& worker : m_workers)
		{
			if (worker.joinable())
			{
				worker.join();
			}
		}
	}
} //end of namespace CTP


#pragma once
#include <future>
#include <functional>
#include <thread>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

namespace CTP
{
	template<typename F, typename... Args>
	using JobReturnType = typename std::result_of<F(Args...)>::type;

	// this is the priority of the jobs. Most jobs shall be ran as Normal priority. 
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
		auto Schedule(Priority priority, F&& f, Args&&... args)
			->std::future<JobReturnType<F, Args...>>
		{
			auto job = std::make_shared<std::packaged_task<JobReturnType<F, Args...>()>>
				(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

			AddJob([job] { (*job)(); }, priority);
			return job->get_future();
		}

		//-----------------------------------------------------------------------------
		/// Adds a job with DEFAULT priority level (Normal). Returns a future.
		//-----------------------------------------------------------------------------
		template <typename F, typename... Args>
		auto Schedule(F&& f, Args&&... args)
			->std::future<JobReturnType<F, Args...>>
		{
			return Schedule(Priority::Normal, std::forward<F>(f), std::forward<Args>(args)...);
		}
		
		// the main function for initializing the pool and starting the threads
		void Init(size_t threadCount);
		void Shutdown();
		void AddJob(std::function<void()>&& job, Priority priority);

	private:
		std::mutex m_guard;
		std::condition_variable m_cvSleepCtrl;
		std::vector<std::thread> m_workers;
		std::map<Priority, std::queue<std::function<void()>>, std::greater<Priority> > m_jobsByPriority;	
	};

} 

