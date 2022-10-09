#include <iostream>
#include <cstring> // for strlen()
#include <cassert> // for assert()

class MyString
{
private:
	char* m_data{ nullptr };
	int m_length{ 0 };

public:
	char* getString() { return m_data; }
	int getLength() { return m_length; }

	friend void swap(MyString& first, MyString& second) noexcept {
		// enable ADL (not necessary in our case, but good practice)
		using std::swap;

		// by swapping the members of two objects,
		// the two objects are effectively swapped
		swap(first.m_data, second.m_data);
		swap(first.m_length, second.m_length);
	}

	MyString() = default;

	~MyString() // destructor
	{
		if (m_data == nullptr) {
			std::cout << "destructor m_data==nullptr" << std::endl;
		}
		else {
			std::cout << "destructor " << m_data << std::endl;
		}
		// We need to deallocate our string
		delete[] m_data;
	}

	MyString(const char* source)
		: MyString()
	{
		std::cout << "MyString(const char* source)" << std::endl;
		if (source == nullptr)
			return;

		// Find the length of the string
		// Plus one character for a terminator
		m_length = static_cast<int>(std::strlen(source)) + 1;

		// Allocate a buffer equal to this length
		m_data = new char[m_length];

		// Copy the parameter string into our internal buffer
		for (int i{ 0 }; i < m_length; ++i)
			m_data[i] = source[i];
	}

	MyString(const MyString& source)
		: MyString()
	{
		std::cout << "Copy constructor" << std::endl;
		MyString temp{ source.m_data };
		swap(*this, temp);
	}

	MyString(MyString&& source) noexcept
		: MyString()
	{
		std::cout << "Move constructor" << std::endl;
		swap(*this, source);
	}

	MyString& operator=(MyString& other) {
		std::cout << "Copy assignment" << std::endl;
		MyString temp{ other.m_data };
		swap(*this, temp);
		return *this;
	}

	MyString& operator=(MyString&& other) noexcept {
		std::cout << "Move assignment" << std::endl;
		swap(*this, other);
		return *this;
	}
};


int main()
{
	MyString hello{ "Hello, world!" };
	{
		MyString copy{ hello }; // use default copy constructor
	} // copy is a local variable, so it gets destroyed here.  The destructor deletes copy's string, which leaves hello with a dangling pointer

	std::cout << hello.getString() << '\n'; // this will have undefined behavior

	return 0;
}