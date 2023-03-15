#include "Task.hpp"
#include <iostream>
using namespace std;

void testFunc1() 
{
  cout << "testFunc1" << "\n";
}

void testFunc2() 
{
  cout << "testFunc2" << "\n";
}

int main() {
    Task t1;
    Task t2;
    
    t1.startWithPriority(prioLowest, &testFunc1);
    t2.startWithPriority(prioNormal, &testFunc2);
    
    t1.stop();
    t2.stop();
}
