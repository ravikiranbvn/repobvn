// -----------------More Exceptional Cpp----------------------------------
// More Exceptional C++ 1 - Herb Sutter 
// #include <fstream>
// #include <iostream>
// using namespace std;

// template<typename In, typename Out>
// void Process(In& in, Out& out)
// {
//     out << in.rdbuf();
// }

// int main(int argc, char* argv[])
// {
//     fstream in, out;

//     if(argc > 1) {in.open  (argv[1], ios::in  | ios::binary);} 
//     if(argc > 2) {out.open (argv[2], ios::out | ios::binary);}

//     Process(in.is_open()  ? in  : cin,
//             out.is_open() ? out : cout);
// }

// More Exceptional C++ 2-2  - Herb Sutter 
// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// int main()
// {
//     vector<int> v{1, 2, 3, 1, 2, 3, 1, 2, 3};
//     v.erase(std::remove(v.begin(), v.end(), 3), v.end());
//     for(auto &i : v) { cout << i << "\n";}
//     return 0;
// }

// More Exceptional C++ 2-3 - Herb Sutter
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cassert>

// using namespace std;

// template<typename FwdIter>
// FwdIter remove_nth(FwdIter first, FwdIter last, size_t n)
// {
//     assert(distance(first, last) >= n);
//     advance(first, n);
    
//     if(first != last)
//     {
//         FwdIter dest = first;
//         return copy(++first, last, dest);
//     }

//     return last;
// }

// int main()
// {
//     vector<int> v{1, 2, 3, 1, 2, 3, 1, 2, 3};
//     v.erase(remove_nth(v.begin(), v.end(), 3), v.end());
//     for(auto i: v) {cout << i << "\n";}

//     return 0;
// }

// More Exceptional C++ 2-3(b) - Herb Sutter
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <cassert>

// using namespace std;

// template<typename T>
// class GreaterThan: public std::unary_function<T, bool>
// {
// public:
//     GreaterThan(T value) : value_(value) { }
//     bool operator()(const T& t) const
//     {
//         return t > value_;
//     }
// private:
//     const T value_;
// };

// template<typename Iter, typename Pred> inline
// Iter find_if_(Iter first, Iter last, Pred pred)
// {
//     while( first != last && !pred(*first) )
//     {
//         ++first;
//     }
    
//     return first;
// }

// bool IsAnyElementGreaterThanFive(vector<int>& v)
// {
//     return find_if_(v.begin(), v.end(), GreaterThan<int>(5))!= v.end();
// }

// int main()
// {
//     vector<int> v{1, 2, 3, 1, 2, 3, 1, 10, 10};
//     cout << IsAnyElementGreaterThanFive(v) << "\n";

//     return 0;
// }