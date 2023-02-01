#include <vector>
#include <iostream>
#include <iterator>
#include <list>
#include <thread>
#include <memory>
#include <sstream>
#include <cassert>
#include <string>
#include <algorithm>
#include <experimental/iterator>

using namespace std;

// join string with a separator
template <typename Iter>
std::string join_strings(Iter begin, Iter end, 
                         char const* const separator)
{
    std::ostringstream os;
    std::copy(begin, end, 
              std::experimental::make_ostream_joiner(os, separator));

    return os.str();
}

template <typename C>
std::string join_strings(C const &c, char const* const separator)
{
    if(c.size() == 0) return std::string{};
    return join_strings(c.begin(), c.end(), separator);
}

int main()
{
    using namespace std::string_literals;
    std::vector<std::string> v1{ "this","is","an","example" };
    std::list<std::string>   v2{ "example", "list" };

    assert(join_strings(v1, " ") == "this is an example");
    assert(join_strings(v2, " ") == "example list");

    return 0;
}

/*
// variadic templates   
template<typename C, typename... Args>
void push_back(C& c, Args&&... args)
{
    (c.push_back(args), ...);
}

int main() 
{
    std::cout << "processing vector" << "\n";
    std::vector<int> v;
    push_back(v, 1, 2, 3, 4);
    std::copy(std::begin(v), std::end(v), 
              std::ostream_iterator<int>(std::cout, " "));
    
    std::cout << "\nprocessing list" << "\n";
    std::list<int> l;
    push_back(l, 3, 4, 5, 6, 7);
    std::copy(std::begin(l), std::end(l),
              std::ostream_iterator<int>(std::cout, " "));

    return 0;
} */
