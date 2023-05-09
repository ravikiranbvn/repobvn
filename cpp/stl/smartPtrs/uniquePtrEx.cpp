#include <memory>
#include <iostream>

using namespace std;

int main() {
    std::unique_ptr<int> ptr(std::make_unique<int>());

    // returns pointer to the old managed object
    cout << "ptr.get() = "<< ptr.get() << endl;
    
    // deletes managed object
    ptr.reset();

    // returns pointer
    cout << "ptr.get() = "<< ptr.get() << endl; 
    
    // make new pointer
    ptr = std::make_unique<int>();

    //returns pointer
    cout << "ptr.get() = "<< ptr.get() << endl; 

    std::unique_ptr<int> ptr1(std::make_unique<int>());

    // move ptr
    ptr1 = std::move(ptr);

    //returns pointer
    cout << "ptr.get() = "<< ptr.get() << endl; 

    //returns pointer
    cout << "ptr1.get() = "<< ptr1.get() << endl; 
    
    return 0;
}