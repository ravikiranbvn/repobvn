#include "ThreadPool.hpp"
using namespace std;

ThreadPool::ThreadPool(size_t threadCount)
{
    initialize(threadCount);
}

ThreadPool::~ThreadPool()
{
    shutDown();
}

void ThreadPool::addTask(Priority priority, std::function<void()> job)
{
    std::unique_lock<std::mutex> ul(m_mutex);
	m_tasksByPriority[priority].emplace(std::move(job));
	m_cv.notify_one();
}

void ThreadPool::handlerTask()
{
	m_workers.push_back(std::thread([this]() {
	std::function<void()> job; 
	{
		std::unique_lock<std::mutex> ul(m_mutex);
		m_cv.wait(ul, [this]() {
		bool allQueuesEmpty = true;
		for (const auto& kvp : m_tasksByPriority) {
			allQueuesEmpty &= kvp.second.empty();
		}   
			return !allQueuesEmpty;
		});

		for (auto& kvp : m_tasksByPriority) {
			auto& jobs = kvp.second; 
			if (jobs.empty()) {
				continue;	
			}
			
			job = std::move(jobs.front()); 
		    jobs.pop();							
		    break;		
		}
	}

	if (job != nullptr)
		job();
	}));
}

void ThreadPool::initialize(size_t threadCount)
{
	m_tasksByPriority[Priority::Normal] = {};
	m_tasksByPriority[Priority::High] = {};
	m_tasksByPriority[Priority::Critical] = {};
	m_workers.reserve(threadCount);

	for (int i = 0; i < threadCount; i++) {
		cout << i << "\n";
		handlerTask();
	}
}

void ThreadPool::shutDown()
{
    m_cv.notify_all();
    for (auto& worker : m_workers) {
       if (worker.joinable())
          worker.join();
    }
}
