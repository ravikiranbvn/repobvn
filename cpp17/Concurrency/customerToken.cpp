// program to simulate customer wait->eat->leave in a restaurant, using concurrency
// inspired from dinning philoshpers problem: https://en.wikipedia.org/wiki/Dining_philosophers_problem

#include <bits/stdc++.h>
#include <chrono>
#include <random>
#include <mutex>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
std::mutex mutex_;      // mutual exclusion for critical regions
std::mutex mo;

enum {
  MAX_TABLES = 5,       // no. of available tables 
  UNKNOWN = -1,
  WAITING=0,            // customer waiting
  HUNGRY=1,             // customer trying to get table
  EATING=2,             // customer is eating
  FINISHED=3            // customer finished eating
};

static int myrand(int min, int max) {
  static std::mt19937 rnd(std::time(nullptr));
  return std::uniform_int_distribution<>(min,max)(rnd);
}

static std::pair<int, bool> get_tableStatus(std::unordered_map<int, bool>& TableMap)
{
   for(auto& eachTable: TableMap)
   {
      if(eachTable.second == false)
        return eachTable;
   }
   return {0, false};
}

void set_tableStatus(std::unordered_map<int, bool>& TableMap, std::pair<int, int> updateStatus)
{
   for(auto& eachTable: TableMap)
   {
       if(eachTable.first  == updateStatus.second)
       {
           if(updateStatus.first == FINISHED)
              eachTable.second = false;
           
           if(updateStatus.first == EATING)
              eachTable.second = true;
       }
   }
}

class Customer {
public:
    Customer(std::string n, std::unordered_map<int, bool> TableMap) :
            m_name(std::move(n)),
            m_cust(&Customer::run, this),
            m_tableMap(TableMap),
            m_state(UNKNOWN),
            m_tableTaken(-1) {}
    
~Customer() { m_cust.join(); }

void test()        
{
  // check for table status
  std::pair<int, bool> availTable = get_tableStatus(m_tableMap);
  if(availTable.first > 0 && availTable.first <= MAX_TABLES)
  {
    if(m_state == HUNGRY && availTable.second == false)
    {
        m_state = EATING;
        m_tableTaken = availTable.first;
        std::pair<int, bool> upPair = {m_state, m_tableTaken};
        set_tableStatus(m_tableMap, upPair);
    } 
  }
}

void get_table()    
{
  mutex_.lock();              // enter critical region
  m_state = HUNGRY;
  test();                     // try to acquire table
  mutex_.unlock();            // exit critical region
}

void leave_table()   
{
  mutex_.lock();                 // enter critical region
  m_state = FINISHED;            // customer has finished eating
  std::pair<int, bool> upPair = {m_state, m_tableTaken};
  set_tableStatus(m_tableMap, upPair);
  std::cout<<"\t\t\t\t\t\t\t\t"<<m_name<<" finished "<<"\n";
  mutex_.unlock();               // exit critical region
}

void wait() {
  m_state = WAITING;
  int duration = myrand(1000, 2000);
  {
	std::lock_guard<std::mutex> g(mo);
	std::cout<<m_name<<" waiting "<<duration<<"ms\n";
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void eat() {
  if(m_state == EATING) {
  int duration = myrand(1000, 2000);
  {
	std::lock_guard<std::mutex> g(mo);
	std::cout<<"\t\t\t\t"<<m_name<<" eating "<<duration<<"ms\n";
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(duration));
 }
}


void run() {
    while (true) {           		// repeat till finised
    wait();            		        // customer is waiting
    get_table();                    // get table
    eat();             		        // yum-yum, spaghetti
    leave_table();                  // leave table
    
    if(m_state == FINISHED)
       break;                       // bye
  }
  
  std::cout<<"\t\t\t\t\t\t\t\t\t\t\t\t"<<m_name<<" bye! "<<"\n";
}
    
private:
    std::string const m_name;
    std::thread m_cust;
    std::unordered_map<int, bool> m_tableMap;
    int m_state;
    int m_tableTaken;
};

int main() {
  // Table mapping
  // table no, occupied ?
  std::unordered_map<int, bool> TableMap;
  
  int tableNo = 1;
  while(tableNo <= MAX_TABLES)
  {
    TableMap.insert(std::pair<int, bool>(tableNo, false));
    tableNo++;
  }
  
  Customer cust1{"ravi", std::ref(TableMap)};
  Customer cust2{"deep", std::ref(TableMap)};
  Customer cust3{"sind", std::ref(TableMap)};
  Customer cust4{"x", std::ref(TableMap)};
  Customer cust5{"y", std::ref(TableMap)};
  Customer cust6{"z", std::ref(TableMap)};
}
