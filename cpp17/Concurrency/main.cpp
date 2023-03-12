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
