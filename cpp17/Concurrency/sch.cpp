#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <functional>

using namespace std::chrono_literals;
using namespace std;

void checkHealthSensor1() {
  std::cout << "checking health in sensor1" << "\n"; 
}

void checkHealthSensor2() {
  std::cout << "checking health in sensor2" << "\n"; 
}

void checkHealthSensor3() {
  std::cout << "checking health in sensor3" << "\n"; 
}

void checkHealthSensor4() {
  std::cout << "checking health in sensor4" << "\n"; 
}

class Task {
public:
    Task(const std::function<void()> job, long n);
    void run();
    Task(const Task &) = delete;
    virtual ~Task();
    
private:
    std::thread m_thread;
    long m_dur;
    std::function<void()> m_execute;
    std::condition_variable m_cv;
};

Task::Task(const std::function<void()> job, long n) : 
           m_dur(n),
           m_execute(job),
           m_thread(&Task::run, this) {}
           
Task::~Task() { m_thread.join();}

void Task::run() {
    std::this_thread::sleep_for(std::chrono::milliseconds(m_dur));
    try {
        if(m_execute)
          m_execute();
    } catch(const std::exception &e) {
      
    } catch(...) {
      std::runtime_error("Unknown exception");
    }
}

class Scheduler {
public:
    Scheduler(size_t num): m_noAllTasks(num) {}
    
    void run(const std::function<void()> job, long n) {
        std::unique_lock<std::mutex> lock(m_mutex);
        if(m_noAllTasks == 0) { m_cv.notify_all(); return;}
        Task task(job, n);
        m_timeAllTasks += n;
        m_noAllTasks--;
        m_cv.notify_one();
    }
    
    void stop() 
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      if(m_cv.wait_for(lock, m_timeAllTasks*100ms, [&] {return m_noAllTasks == 0;}))
        std::cerr << "finished all tasks" << "\n";
      else
        std::cerr << "timed out after" << m_timeAllTasks << "\n";
    }
    
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    size_t m_noAllTasks;
    size_t m_timeAllTasks;
};

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    
    Scheduler sch(4);
    
    sch.run(&checkHealthSensor1, 1000);
    sch.run(&checkHealthSensor2, 10);
    sch.run(&checkHealthSensor3, 100);
    sch.run(&checkHealthSensor4, 3000);  
    sch.stop();
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Waited: " << duration.count() << std::endl;
}
