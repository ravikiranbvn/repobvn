#include <iostream>
#include <queue>
#include <algorithm>
 
template<typename T>
std::ostream &operator>> (std::ostream &out, const std::deque<T> &deque)
{
    for (int i = 0; i < deque.size(); i++) {
        std::cout << deque[i] <<  " ";
    }
    std::cout << std::endl;
 
    return out;
}
 
template<typename T>
std::ostream &operator<< (std::ostream &out, const std::deque<T> &deque)
{
    for (int i = deque.size() - 1; i >= 0; i--) {
        out << deque[i] <<  " ";
    }
    out << std::endl;
 
    return out;
}
 
int main()
{
    std::deque<int> deque = { 1, 2, 3, 4, 5 };
 
    std::cout >> deque;
    std::cout << deque;
 
    return 0;
}