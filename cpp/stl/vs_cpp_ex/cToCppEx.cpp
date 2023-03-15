#include <cstdio>
#include <iostream>

struct Printer {
    static void print_str(const char * str) {
        puts(str);
    }
};

template <typename P>
class MyClass {
    private:
        const char * my_name_ = "MyClass";
        P printer_;
    public:
        void print_my_name () {
            printer_.print_str(my_name_);
        }
};

int main() {

    MyClass<Printer> my_obj;
    my_obj.print_my_name();

    return 0;
}