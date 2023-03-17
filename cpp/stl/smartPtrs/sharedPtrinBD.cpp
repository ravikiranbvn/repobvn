#include <iostream>
#include <memory>
using namespace std;

class Base {
public:
	Base()
	{
		cout << "Constructing Base" << endl;
	}
	~Base()
	{
		cout << "Destructing Base" << endl;
	}
	
	void print() 
	{
	    cout << "base class" << "\n";
	}
	
};

class Derived : public Base {
public:
	Derived()
	{
		cout << "Constructing Derived" << endl;
	}
	~Derived()
	{
		cout << "Destructing Derived" << endl;
	}
	
	void print() 
	{
	    cout << "Derived class" << "\n";
	}
};

class test {
public:
    test() {}

    ~test() {}

    void 
    input(std::shared_ptr<Base> pbase) {
        cout << "input called" << "\n";
        static_cast<Derived*>(pbase.get())->print();
    }
};

int main()
{
    test t;
	t.input(std::make_shared<Derived>());
}
