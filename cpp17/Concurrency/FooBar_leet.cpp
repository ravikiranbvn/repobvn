#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
    
void printFoo() {
    cout << "foo";
}
    
void printBar() {
    cout << "bar";
}
    
class FooBar {
public:
    FooBar(int n) {
        m_times = n;
        m_turn = 0;
    }
    
    void foo(function<void()> printFoo) {
        for(int i=0; i < m_times; i++) {
            std::unique_lock<std::mutex> lock(m_mutex);
            while(m_turn == 1) {
                m_cv.wait(lock);
            }
    
            printFoo();
            m_turn = 1;
            m_cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        for(int i=0; i < m_times; i++) {
            std::unique_lock<std::mutex> lock(m_mutex);
            while(m_turn == 0) {
                m_cv.wait(lock);
            }
        
            printBar();
            m_turn = 0;
            m_cv.notify_all();
        }
    }

private:
    int m_times;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_turn;
};

int main() {
 
 FooBar obj(100);

 std::thread t1(&FooBar::foo, &obj, &printFoo);
 std::thread t2(&FooBar::bar, &obj, &printBar);
 
 t1.join();
 t2.join();
 
 return 0;   
}
