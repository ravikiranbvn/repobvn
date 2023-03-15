#include "iostream"
#include "thread"
#include "mutex"
#include "condition_variable"
using namespace std;

std::mutex mu;
std::condition_variable cond;
int count = 1;

void PrintOdd()
{
    for( ; ; )
    {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker,[](){ return (count%2 == 1); });
    cout<< "From Odd:    " <<  count << endl;
    count++;
    locker.unlock();
    cond.notify_all();
    }

}

void PrintEven()
{
    for( ; ; )
    {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker,[](){return (count%2 == 0);});
    cout<< "From Even: " << count << endl;
    count++;
    locker.unlock();
    cond.notify_all();
    }
}

int main()
{
    std::thread t1(PrintOdd);
    std::thread t2(PrintEven);
    t1.join();
    t2.join();
    return 0;
}