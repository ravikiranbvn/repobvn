// function template
// #include <iostream>
// using namespace std;

// template <typename X> //class or typename keyword can be used
// X func(X a, X b)
// {
//     return a;
// }

// int main()
// {
//     cout << func(10, 12) << "\n";
//     cout << func('R', 'S') << "\n";
//     cout << func(212.09, 227.90) << "\n";
// }

// C++ Class Templates With Multiple Parameters
// #include <iostream>
// using namespace std;

// template<class A, class B>
// class Sample
// {
// public:
//     Sample(A x, B y)
//     {
//         a = x;
//         b = y;
//     }

//     void display()
//     {
//         cout << "The inputs are: " << a << " and " << b << endl;
//     }

//     private:
//     A a;
//     B b;
// };

// int main()
// {
// 	// instantiation
// 	Sample<int, char> ob1 (24, 'A');
	
// 	// instantiation 
// 	Sample<int, float> ob2(22.56, 34.9);
	
// 	//Calling the display function to see the output
//     ob1.display();
// 	ob2.display();
	
// 	return 0;
// }

// Class template in c++ example:
// #include <iostream>
// using namespace std;

// template<class C>
// class A 
// {
// public:
//     A(C x, C y)
//     {
//        a = x;
//        b = y; 
//     }

//     void show()
//     {
//         cout << "addition = " << add() << "\n";
//     }

// private:
//     C add()
//     {
//         return a + b;
//     }

//     C a;
//     C b;
// };

// int main()
// {
//     A aI(10, 10);
//     aI.show();

//     A aF(10.233, 9.898);
//     aF.show();
// } 

// Function Specialization
// #include <iostream>
// using namespace std;

// template <class T>
// T max_(T a, T b)
// {
//     return a > b ? a: b;
// }

// int main()
// {
//     cout << max_(80, 96) << "\n";
//     cout << max_('a', 'z') << "\n";
//     cout << max_(11.1, 18.2) << "\n" ; 
// }

// Class specialization example
// #include <iostream>
// using namespace std;

// template <class T>
// class Test
// {
// public:
//     Test()
//     {
//         cout << "generalized template" << "\n";
//     }
// };

// template <>
// class Test<int>
// {
// public:
//     Test()
//     {
//         cout << "specialized template" << "\n";
//     }
// };

// int main()
// {
//     Test<int> a;
//     Test<char> b;
//     Test<float> c;
// }

// Can we pass non-type parameters to templates?
// #include <iostream>
// #include <string>
// using namespace std;

// template <std::string * temp> //pointer to object
// void f()
// {
//    cout << *temp << endl;
// }

// template <std::string & temp> //reference to object
// void g()
// {
//      cout << temp << endl;
//      temp += "...appended some string";
// }

// std::string s; //must not be local as it must have external linkage!

// int main() {
//         s = "can assign values locally";
//         f<&s>();
//         g<s>();
//         cout << s << endl;
//         return 0;
// }

// template with predicate (functor)
// #include <iostream>
// #include <vector>
// using namespace std;

// template<typename Container, typename Predicate>
// void out_filtered(Container C, Predicate f) {
//     for(auto x: C) {
//         if(f(x))
//            cout << x << " ";
//     std::cout << " " << "\n";
//     }
// }

// template<typename T>
// bool even(T x) {
//    return x % 2 == 0;
// }

// template<typename T>
// class InRange
// {
// public:
//     InRange(T from, T to):a{from}, b{to} {}
     
//     bool operator() (T& value) {
//         return a <= value && value <= b;
//     }

//     private: 
//     T a;
//     T b;
// };

// int main()
// {
//     std::vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
//     // out_filtered(v, even<int>);
//     // out_filtered(v, InRange<int>(5, 10));

//     // using lamda expression
//     // out_filtered(v, [](int x) {return x%2 == 0;});
//     int from; int to;
//     std::cin >> from >> to;
//     out_filtered(v, [from, to](int x) {return from <= x && x <= to;});

//     return 0;
// }

// ---------------dummy-------------
#include <iostream>
using namespace std;

int main()
{
    std::cout << "dummy()" << "\n";
}

