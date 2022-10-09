// #include <iostream>
// #include <vector>
// #include <algorithm>

// template<typename T>
// class Sum 
// {
// T& sum;
// public:
//     Sum(T& init): sum{init} {}
//     void operator() (T value) {
//         sum += value;
//     }
// };

// int main() 
// {
//     std::vector<double> v{22.3, 22.5, 45.8};
//     double sum = 0.0;

//     // sum passing with ref to not make a new copy and give 0 as sum
//     // std::for_each(v.begin(), v.end(), Sum<double>(sum));

//     // using lamda function
//     std::for_each(v.begin(), v.end(), [&sum](double k){sum += k;});
//     std::cout << sum << "\n"; 
// }

/* #include <iostream>
int main()
{
    []()->void {std::cout << "Hello world!" << "\n";} ();
    return 0;
} */

// #include <iostream>
// #include <algorithm>
// #include <vector>

// int main()
// {
//   std::vector v {1300, 240, 10, 67, 8, 9};
//   std::sort(v.begin(), v.end(), [](auto x, auto y) {return y > x;});
//   std::for_each(v.begin(), v.end(), [](auto x){std::cout << x << "\n";});

//   return 0;
// }

// functional programming 
/*#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <functional>

void* operator new(std::size_t size){
    return malloc(size);
}

void operator delete(void* pointer){
    return free(pointer);
}

void operator delete(void* pointer, std::size_t size){
    return free(pointer);
}

template<typename T, typename F>
T foreach(T t, F f){
    for(auto x:t)
        f(x);
    return t;
}

template <typename T, typename F>
T map(T v, F f){
    for(auto &x: v)
        x = f(x);
    return v;
}

template<typename T>
std::vector<T> read() {
    std::vector<T> v;
    for(T x; std::cin >> x;)
       v.push_back(x);
    
    return v;
}

template<typename T, typename F>
T reduce(std::vector<T> v, F f, T init){
    T result = init;
    for(auto x: v)
       result = f(result, x);
    return result;
}


int main()
{
    auto sum = reduce(
               foreach(
                map(
                    read<int>(),
                    [](int x){return x*x*x;}
                ),
                [](auto x){std::cout << x << " ";}
               ),
               [](int sum, int v) {return sum + v;}, 0
    );

    std::cout << "sum of cubes" << sum << "\n";
    
    return 0;
}*/

#include <iostream>
int main()
{
    return 0;
}