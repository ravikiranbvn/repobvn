#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <functional>

using namespace std;

template <typename T>
void negate_all(vector<T>& v)
{
    for_each(v.begin(), v.end(), [](T& n) { n = -n; });
}

// Prints to the console each element in the vector object.
template <typename T>
void print_all(const vector<T>& v)
{
    for_each(v.begin(), v.end(), [](const T& n) { cout << n << endl; });
}

// Ex 6
class Scale
{
public:
    // The constructor.
    explicit Scale(int scale) : _scale(scale) {}

    // Prints the product of each element in a vector object
    // and the scale value to the console.
    void ApplyScale(const vector<int>& v) const
    {
        for_each(v.begin(), v.end(), [=](int n) { cout << n * _scale << endl; });
    }

private:
    int _scale;
};

int main()
{   
    // Ex 1
    auto y = [](int x, int y){return y + x;};
    cout << y(2, 3) << "\n";
    
    // Ex 2
    cout << [](int x, int y) {return x + y;} (5, 10) << "\n";
    
    // Ex 3
    vector<int> v;
    for(int i=0; i < 9; i++){
        v.push_back(i);
    }
    
    int eve_count = 0;
    for_each(v.begin(), v.end(), [&eve_count](int n){
        if(n%2 == 0)
          ++eve_count;
    });
    cout << "count of even no's:" << eve_count << "\n";

    // Ex 4
    list<int> ll;

    ll.push_back(13);
    ll.push_back(17);
    ll.push_back(42);
    ll.push_back(46);
    ll.push_back(99);

    auto res = find_if(ll.begin(), ll.end(), [](int n) { return n%2 == 0;});

    if(res != ll.end()) {
        cout << "first even no in list:" << *res << "\n";
    }
    else {
        cout << "no even no's in list" << "\n";
    }

    // Ex 5
    // The following code declares a lambda expression that returns
    // another lambda expression that adds two numbers.
    // The returned lambda expression captures parameter x by value.
    auto addtwointegers = [](int x) -> function<int(int)> {
        return [=](int y) { return x + y; };
    };

    // The following code declares a lambda expression that takes another
    // lambda expression as its argument.
    // The lambda expression applies the argument z to the function f
    // and multiplies by 2.
    auto higherorder = [](const function<int(int)>& f, int z) {
        return f(z) * 2;
    };

    // Call the lambda expression that is bound to higherorder.
    auto answer = higherorder(addtwointegers(7), 8);

    // Print the result, which is (7+8)*2.
    cout << answer << endl;
    
    // Ex 6
    vector<int> values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    values.push_back(4);

    // Create a Scale object that scales elements by 3 and apply
    // it to the vector object. Does not modify the vector.
    Scale s(3);
    s.ApplyScale(values);

    // Ex 7
    vector<int> vi;
    vi.push_back(34);
    vi.push_back(-43);
    vi.push_back(56);

    print_all(vi);
    negate_all(vi);
    cout << "After negate_all():" << endl;
    print_all(vi);

    return 0;
}