#include "Task.hpp"
#include <cstring>

Task::Task() : 
           m_execute(nullptr),
           m_thread(&Task::run, this) {}
           
Task::~Task() { 
    stop();
}

void Task::configure() {

}

void Task::startWithPriority(int priority, const std::function<void()> job) {
    int get_policy;
    struct sched_param get_param;

    int res = pthread_getschedparam(m_thread.native_handle(), &get_policy, &get_param);
    if (res != 0) {
        throw std::runtime_error("Error accessing scheduling params" + std::to_string(res));
    }
    
    get_param.sched_priority = priority;
    pthread_t id = pthread_self();
    if(pthread_setschedparam(m_thread.native_handle(), &get_policy, &get_param)) {
        std::cerr << "Failed to set Thread scheduling : " 
                  << std::strerror(errno) << "\n";
    }
}

void uhd::set_thread_priority(float priority, bool realtime)
{
    check_priority_range(priority);

    // when realtime is not enabled, use sched other
    int policy = (realtime) ? SCHED_RR : SCHED_OTHER;

    // we cannot have below normal priority, set to zero
    if (priority < 0)
        priority = 0;

    // get the priority bounds for the selected policy
    int min_pri = sched_get_priority_min(policy);
    int max_pri = sched_get_priority_max(policy);
    if (min_pri == -1 or max_pri == -1)
        throw uhd::os_error("error in sched_get_priority_min/max");

    // set the new priority and policy
    sched_param sp;
    sp.sched_priority = int(priority * (max_pri - min_pri)) + min_pri;
    int ret           = pthread_setschedparam(pthread_self(), policy, &sp);
    if (ret != 0)
        throw uhd::os_error("error in pthread_setschedparam");
}


void uhd::set_thread_name(std::thread* thrd, const std::string& name)
{
    pthread_setname_np(thrd->native_handle(), name.substr(0, 16).c_str());
}

void Task::run() {
    /*try {
        if(m_execute)
          m_execute();
    } catch(const std::exception &e) {
      
    } catch(...) {
      std::runtime_error("Unknown exception");
    }*/
    
     if(m_execute)
          m_execute();
}

void Task::stop() {
   m_thread.join(); 
}
