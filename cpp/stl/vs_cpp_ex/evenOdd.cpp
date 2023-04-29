#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
using namespace std;

std::mutex mu;
std::condition_variable cond;
int count = 0;

void printOdd()
{
    for(; count < 100;)
    {
        std::unique_lock<std::mutex> locker(mu); 
        cond.wait(locker, [&] () -> int { return count;});
        cout<< "From Odd:    " <<  count << endl;
        count++;
        locker.unlock();
        cond.notify_one();
    }
}

void printEven()
{
    for(; count < 100;)
    {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker,  [&] () -> int { return count;});
        cout<< "From Even: " << count << endl;
        count++;
        locker.unlock();
        cond.notify_one();
    }
}

int main()
{
    std::thread t1(printOdd);
    std::thread t2(printEven);
    
    t1.join();
    t2.join();
    return 0;
}