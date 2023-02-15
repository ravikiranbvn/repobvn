// Program to create a atomic counter and control the thread execution with a condition on counter

#include <thread>
#include <iostream>
#include <mutex>
#include <vector>

class atomic_counter {
public:
    void increment() {
        std::unique_lock<std::mutex> l(m_mutex);
        m_counter++;
    }
    
    void decrement() {
        std::unique_lock<std::mutex> l(m_mutex);
        m_counter--;
    }
    
    int value() {
        std::unique_lock<std::mutex> l(m_mutex);
        return m_counter;
    }

    bool increment_if_less_than(int val, std::thread::id id) {
        std::unique_lock<std::mutex> l(m_mutex);
        if (m_counter < val) {
            m_counter++;
            std::cout << "thread " << id << " " << m_counter << "\n";
            return true;
        }   
        return false;
    }
    
    
private:
    int m_counter = 0;
    std::mutex m_mutex;
};
 
int main() {
    atomic_counter counter;
 
    auto thread_func = [&counter] () {
        std::thread::id this_id = std::this_thread::get_id();
        while(counter.increment_if_less_than(10, this_id)) {
        }
    };
 
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        std::cout << "thread" << i << "started \n";
        threads.emplace_back(thread_func);
    }
    for (auto& thread : threads) {
        thread.join();
    }
 
    std::cout << counter.value() << '\n';
}
