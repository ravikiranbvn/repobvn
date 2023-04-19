#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <array>

std::vector<std::string> v;

void printArray(const std::array<std::string, 5>& myArray) {
    for (auto element : myArray)
        std::cout << std::quoted(element) << ' ';
    std::cout << '\n';
}

void add_to_vec(const std::string& str)
{
    std::cout << "calling copy" << "\n"; 
    v.push_back(str);
}

void add_to_vec(std::string&& str)
{
    std::cout << "calling move" << "\n";
    v.push_back(std::move(str));
}

int main()
{
    std::array<std::string, 5> testArr{"hello", "world", "please", "catch", "34545"};
    
    std::cout << "Elements after before ops" << "\n";
    printArray(testArr);
    
    // uses the add_to_vec(const T&) overload, which means 
    // we'll incur the cost of copying str
    add_to_vec(testArr[0]);
    std::cout << "After copy, testArr[0] is " << std::quoted(testArr[0]) << '\n';
 
    // uses the rvalue reference add_to_vec(T&&) overload, 
    // which means no strings will be copied; instead, the contents
    // of str will be moved into the vector.  This is less
    // expensive, but also means str might now be empty.
    add_to_vec(std::move(testArr[1]));
    std::cout << "After move, testArr[1] is " << std::quoted(testArr[1]) << '\n';
    
    add_to_vec(testArr[2]);
    std::cout << "After copy only, testArr[2] is " << std::quoted(testArr[2]) << '\n';
    
    std::cout << "The contents of the vector are { " << std::quoted(v[0])
                                             << ", " << std::quoted(v[1])
                                             << ", " << std::quoted(v[2]) << " }\n";

    std::cout << "Elements after all ops" << "\n";
    printArray(testArr);
    
    std::cout << "no of elements in array:" << sizeof(testArr)/sizeof(testArr[0]);
}
