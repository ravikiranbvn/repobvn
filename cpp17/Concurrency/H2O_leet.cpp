#include<bits/stdc++.h>
#include<mutex>
#include<thread>
#include<condition_variable>
#include<functional>

using namespace std;

std::string water = "HOH";

void printHydrogen() {
    cout << "H";
}

void printOxygen() {
    cout << "O";
}

class H2O {
public:
    H2O(): m_mutex{}, m_cv{}, m_turn(0) {}

    void hydrogen(function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_turn == 2) {
            m_cv.wait(lock);
        }
        
        releaseHydrogen();

        ++m_turn;
        m_cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lock(m_mutex);
        while(m_turn < 2) {
            m_cv.wait(lock);
        }
        
        releaseOxygen();

        m_turn = 0;
        m_cv.notify_all();
    }
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    int m_turn;    
};

int main() {
    H2O obj;
        
    std::thread t1(&H2O::hydrogen, &obj, &printHydrogen);
    std::thread t2(&H2O::oxygen, &obj, &printOxygen);
    
    t1.join();
    t2.join();
}
