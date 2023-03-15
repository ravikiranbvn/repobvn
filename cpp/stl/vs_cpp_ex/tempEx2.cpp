#include <iostream>
#include <utility>

//----------non-type Templates---------------------
template <class T, int size>
class Ex
{
public:
    Ex()
    {
        for(int i=0; i < size; i++) {
            a[i] = i;
        }
    }

    T &operator[](int i)
    {
        if (i < 0 || i > size - 1)
        {
            std::cout << "Index value of " << i << " is out-of-bounds.\n";
            exit(1);
        }
        return a[i];
    }

private:
    T a[size];
};

template<typename T, size_t n>
void printValues(T const* arr, const int size)
{
    for(size_t i = 0; i < n; ++i)
    { 
        std::cout << arr[i] << ' ';
    } 
    std::cout << std::endl;
}

int main()
{
    Ex<int, 10> e;
    printValues<int, 10>(&e[0], 10);
    return 0;
}
