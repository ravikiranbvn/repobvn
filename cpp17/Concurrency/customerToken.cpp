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
   std::pair<int, bool> foundP{0, false};
   for(auto& eachTable: TableMap)
   {
      if(eachTable.second == false)
      {
        eachTable.second = true;
        foundP = make_pair(eachTable.first, eachTable.second);
        break;
      }
   }
   
   return foundP;
}

static void set_tableStatus(std::unordered_map<int, bool>& TableMap, std::pair<int, bool> updateStatus)
{
   for(auto& eachTable: TableMap)
   {
       if(eachTable.first  == updateStatus.first)
       {
          eachTable.second = updateStatus.second;
          break;
       }
   }
}

class Customer {
public:
    Customer(std::string n, std::unordered_map<int, bool>& TableMap) :
            m_name(std::move(n)),
            m_tableMap(TableMap),
            m_state(UNKNOWN),
            m_tableTaken(-1),
            m_cust(&Customer::run, this) {}
    
~Customer() 
{ 
  m_cust.join();  
}

void test()        
{
  // check for table status
  std::pair<int, bool> availTable = get_tableStatus(m_tableMap);
  if(availTable.first > 0 && availTable.first <= MAX_TABLES)
  {
    if(m_state == HUNGRY && availTable.second == true)
    {
        m_state = EATING;
        m_tableTaken = availTable.first;
        std::cout << "name = " << m_name << " table =" << m_tableTaken << "\n";
    } 
  }
  else
    m_state = UNKNOWN; 
}

void get_table()    
{
  std::lock_guard<std::mutex> lk(mutex_);     // enter critical region
  if(m_state == WAITING || m_state == UNKNOWN) {
      m_state = HUNGRY;
      test();                     	     // try to acquire table
    }
}

void leave_table()   
{
  std::lock_guard<std::mutex> lk(mutex_);   // enter critical region
  if(m_state == FINISHED) {      	    // customer has finished eating
    std::pair<int, bool> upPair = {m_tableTaken, false};
    set_tableStatus(m_tableMap, upPair);
    std::cout<<"\t\t\t\t\t\t\t\t"<<m_name<<" finished "<<"\n";
  }
}

void wait() {
  if(m_state == UNKNOWN) {
    m_state = WAITING;
    int duration = myrand(1000, 2000);
    {
        std::lock_guard<std::mutex> g(mo);
        std::cout<<m_name<<" waiting "<<duration<<"ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
  }
}

void eat() {
  if(m_state == EATING) {
    int duration = myrand(1000, 2000);
    {
	    std::lock_guard<std::mutex> g(mo);
	    std::cout<<"\t\t\t\t"<<m_name<<" eating "<<duration<<"ms\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    m_state = FINISHED;
  }
}

void run() {
    while (true) {           		// repeat till finised
    get_table();                        // get table
    wait();            		        // customer is waiting
    eat();             		        // eat
    leave_table();                  	// leave table
    
    if(m_state == FINISHED)
       break;
  }
  
  std::cout<<"\t\t\t\t\t\t\t\t\t\t\t\t"<<m_name<<" bye! "<<"\n";
}
    
private:
    std::string const m_name;
    std::unordered_map<int, bool>& m_tableMap;
    int m_state;
    int m_tableTaken;
    std::thread m_cust;
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
  Customer cust7{"z1", std::ref(TableMap)};
  Customer cust8{"z2", std::ref(TableMap)};
  Customer cust9{"z3", std::ref(TableMap)};
  Customer cust10{"z4", std::ref(TableMap)};
  
  return 0;
}
