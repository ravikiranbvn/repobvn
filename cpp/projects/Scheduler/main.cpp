#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "ThreadPool.hpp"
#include <thread>

using namespace std::chrono_literals;
using namespace std;
using namespace std::literals::chrono_literals;

bool m_shutdown = false;

void checkHealthSensorCritical() 
{
  const auto start = std::chrono::steady_clock::now();
  while(1) {
   cout << "critical priority task" << "\n";
   //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   auto now = std::chrono::steady_clock::now();
   if(std::chrono::duration_cast<std::chrono::seconds>(now - start) >= 10s) {
     break;
   }
  } 
}

void checkHealthSensorHigh()
{
  const auto start = std::chrono::steady_clock::now();
  while(true) {
  cout << "high priority task" << "\n";
  //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  auto now = std::chrono::steady_clock::now();
   if(std::chrono::duration_cast<std::chrono::seconds>(now - start) >= 10s) {
     break;
   }
  }
}

void checkHealthSensorNormal()
{
  const auto start = std::chrono::steady_clock::now();
  while(1) {
  cout << "normal priority task" << "\n";
  //std::this_thread::sleep_for(std::chrono::milliseconds(500));
  auto now = std::chrono::steady_clock::now();
  if(std::chrono::duration_cast<std::chrono::seconds>(now - start) >= 10s) {
     break;
   }
  }
}

int main()
{
  ThreadPool tp(3);
	tp.startWithPriority(Priority::Normal, &checkHealthSensorNormal);
	tp.startWithPriority(Priority::High,   &checkHealthSensorHigh);
	tp.startWithPriority(Priority::Critical, &checkHealthSensorCritical);      
  tp.shutDown();

	return 0;
}
