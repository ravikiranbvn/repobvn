// https://www.codementor.io/@sandesh87/the-rule-of-five-in-c-1pdgpzb04f

#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Student {
private:
  int id;
  char* name;

public:
  // default constructor
  Student() {
    cout << "default constrcutor called" << "\n";
    this->id = 0;
    this->name = nullptr;
  }
  
  // parameterized constructor
  Student(const char* name, const int id) {
    this->id = id;
    this->name = new char[strlen(name) + 1];
    std::strcpy(this->name, name);
    cout << "parameterized constructor called" << "\n"
         << "name=" << this->name 
         << " id="   << this->id << "\n";
  }

  // copy constructor
  Student(const Student& other) {
    this->id = other.id;
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    cout << "copy constructor called" << "\n"
         << "name=" << this->name 
         << " id="   << this->id << "\n";
  }

  // copy assignment
  Student& operator=(const Student& rhs) {
  // self-asignment check
  if (this != &rhs) {
    this->id = rhs.id;
    char *tmp = new char[strlen(rhs.name) + 1];
    strcpy(tmp, rhs.name);

    // delete old data
    if (this->name) {
      delete[] this->name; }
      this->name = tmp;
    }

    cout << "copy assignment op. called" << "\n"
         << "name=" << this->name 
         << " id="   << this->id << "\n";
    
    return *this;
   }
   
   // destructor
   ~Student() {
    cout << "destructor called" << "\n" 
         << "name=" << this->name 
         << " id="   << this->id << "\n";
    delete[] this->name;
  }

  // move constructor
  Student(Student&& other) {
  
   this->id = other.id;
   this->name = other.name;
   other.name = nullptr;
   cout << "move constructor called" << "\n"
        << "name=" << this->name 
        << " id="   << this->id << "\n";
  }

  // move assignment
  Student& operator=(Student&& rhs) {
  // self-asignment check
  if (this != &rhs) {
    this->id = rhs.id;
    
    // delete old data
    if (this->name) {
    delete[] this->name;}
        this->name = rhs.name;
        rhs.name = nullptr;
    }

    cout << "move assignment op. called" << "\n"
        << "name=" << this->name 
        << " id="   << this->id << "\n";

    return *this;
  }
};

Student foo() {
  Student s1("Arnold", 15);
  return s1;
}

int main()
{
   Student s1("John", 10);
   Student s2 = s1; // copy constructor
   Student s3;
   s3 = s1;         // copy assignment

   Student s4("Jane", 12);
   Student s5 = std::move(s4); // move constructor
   Student s6;
   s6 = std::move(s5);         //move assignment

   //Student someStu = foo();    // move assignemnt
   
   return 0;
}
