#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

struct A
{
    std::string s;
    int k;
 
    A() : s("test"), k(-1) {
        std::cout << "constructor called" << "\n";
    }
    A(const A& other) : s(other.s), k(other.k) { 
        std::cout << "copy constructor called \n"; 
    }

    A(A&& other) noexcept :
        s(std::move(other.s)),       // explicit move of a member of class type
        k(std::exchange(other.k, 0)) // explicit move of a member of non-class type
    {
        std::cout << "move constructor called \n";
    }

    A& operator=(const A& other)
    {
        s = other.s;
        std::cout << "copy assigned  called \n";
        return *this;
    }
 
    A& operator=(A&& other)
    {
        s = std::move(other.s);
        std::cout << "move assigned called \n";
        return *this;
    }
};

 
int main()
{
    A a1;
    std::cout << "Before move, a1.s = " << std::quoted(a1.s)
        << " a1.k = " << a1.k << '\n';
 
    A a2 = std::move(a1); // move-constructs from xvalue
    std::cout << "After move, a1.s = " << std::quoted(a1.s)
        << " a1.k = " << a1.k << '\n';
     std::cout << "After move, a2.s = " << std::quoted(a2.s)
        << " a2.k = " << a2.k << '\n';

    std::cout << "--copy operations------" << "\n";

    A a3, a4;
    a3 = a2;

    std::cout << "After copy assign, a3.s = " << std::quoted(a3.s)
        << " a3.k = " << a3.k << '\n';

    a4 = std::move(a1);
    std::cout << "After copy assign, a4.s = " << std::quoted(a4.s)
        << " a4.k = " << a4.k << '\n';
    
    std::cout << "---move operations---" << "\n";
    A a5, a6;
    a5 = std::move(a2);

    std::cout << "After move assign, a3.s = " << std::quoted(a3.s)
        << " a3.k = " << a3.k << '\n';

    a6 = std::move(a1);
    std::cout << "After move assign, a4.s = " << std::quoted(a4.s)
        << " a4.k = " << a4.k << '\n';
}
