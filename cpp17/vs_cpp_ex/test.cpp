// #include <iostream>
// #include <stdexcept>
// #include <memory>
// #include <vector>
// #include <fstream>
// using namespace std;

// class A {
//   static int i;
//   int j;
// };

// int A::i;
// int main()
// {
//     cout << sizeof(A) << "\n";
//     return 0;
// }

// class Host {
//     int a;
// public:
//     class Nested {
//         Host h; // cannot create a object, without definition of class is complete
//     public:
//         Nested() {
//             h.a = 15;
//         }
//         int get() {
//             return h.a;
//         }
//     };
// };

// int main() {
//     Host::Nested foo;
//     cout << foo.get();

//     return 0;
// }

// ------------------------------------------------------------------
// struct intArray
// {
//     intArray(): p(nullptr) {}
//     explicit  intArray(std::size_t s):
//       p(new int[s])  {}
    
//     ~intArray()
//     {
//         delete[] p;
//     }

//     int* p;
// };

// void excercise(int* b, int* e) 
// {
//     std::vector<int> v(b, e);

//     intArray p(v.size());

//     std::ifstream in("ints");
//     // exception occurs here;
// }

// int main()
// {
// }

// ------------------------------------------------------------------
// #include <memory>
// #include <iostream>

// struct MyObject {
//     int param_ { 0 };
//     void SetParam(int p) {param_ = p; }
// };

// std::unique_ptr<MyObject> BuildObject(int param) {
//     auto p = std::make_unique<MyObject>();
//     p->SetParam(param);
//     // initialize...
//     return p;
// }

// int main() {
//     auto ptr = BuildObject(10);
//     std::cout << ptr->param_ << "\n";

//     std::shared_ptr<MyObject> shared = BuildObject(100);
//     std::cout << shared->param_ << "\n";
// }

// ------------------------------------------------------------------
// #include <memory>
// #include <iostream>
// #include <filesystem>
// #include <fstream>
// #include <fmt/core.h> // replace with <format> in C++20

// namespace fs = std::filesystem;

// void display(std::string_view title, auto val) {
//     std::cout << fmt::format("{} {}\n", title, val); // replace with std::format in C++20
// }

// void createTempFile(const fs::path& name) {
//     display("creating temp file at", name.string());
//     std::ofstream entry(name);
//     entry << "Hello World";
// }

// void printContent(const fs::path& name) {
//     std::ifstream inFile{ name, std::ios::in | std::ios::binary };
//     if (!inFile)
//         throw std::runtime_error("Cannot open " + name.string());
    
//     const auto fsize = static_cast<size_t>(fs::file_size(name)); // assume no errors...

//     auto buf = std::make_unique<char[]>(fsize+1);

//     inFile.read(buf.get(), fsize);
//     if (!inFile)
//         throw std::runtime_error("Could not read the full contents from " + name.string());

//     display("file contents:", buf.get());
//     display("last letter (value):", static_cast<int>(buf[fsize]));
// }

// int main() {
//     const auto tempFile = fs::temp_directory_path() / "hello.txt";

//     createTempFile(tempFile);

//     try {
//         printContent(tempFile);
//     }
//     catch (const std::exception& ex) {
//         display("exception:", ex.what());
//     }

//     return 0;                                        
// }

// ------------------------------------------------------------------
// #include <memory>
// #include <iostream>
// #include <string_view>
// #include <fmt/core.h> // replace with <format> in C++20

// struct BaseObject {
//     virtual ~BaseObject() = default;

//     virtual double calcArea() const noexcept = 0;
// };

// struct Rectangle : BaseObject {
//     Rectangle(double a, double b) : a_(a), b_(b) { }

//     double calcArea() const noexcept override { return a_ * b_; }

//     double a_ { 0.0};
//     double b_ { 0.0};
// };

// int getUserInput() { return 10; }
// void display(std::string_view title, double val) {
//     std::cout << fmt::format("{} {}\n", title, val); // replace with std::format in C++20
// }

// BaseObject* createShape(int userInput) {
//     if (userInput > 0)
//         return new Rectangle(10, 5);

//     return nullptr;
// }

// void processShape() {
// 	std::unique_ptr<BaseObject> pObj { createShape(getUserInput()) };
    
//     if (pObj) {
// 	    const auto area = pObj->calcArea();
//         display("area is", area);
//     }
// }

// int main() {
//     processShape();

//     return 0;                                        
// }

// ---------------dummy-------------
#include <iostream>
using namespace std;

int main()
{
    std::cout << "dummy()" << "\n";
}