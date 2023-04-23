#include <memory>
#include <iostream>
#include <optional>
#include <string_view>
#include <string>
#include <format>

using namespace std;

struct Data {
    int i { 0 };
    double j {0.0};
};

class Package {
public:
    Package(std::string name, double m) 
    : name_(std::move(name))
    , mass_(m)
    , extra_(m > 100.0 ? new Data{} : nullptr ) 
    { 

    }

    ~Package() { }

    // copy constructor
    Package(const Package& other) 
    : name_(other.name_)
    , mass_(other.mass_)
    , extra_(other.extra_ ? new Data(*(other.extra_)) : nullptr)
    {

    }
    
    // move constructor
    // A move constructor enables the resources owned by an rvalue object to be moved into an lvalue without copying
    // The move constructor is much faster than a copy constructor because it doesn't allocate memory nor does it copy memory buffers
    Package(Package&& other) 
    : name_(std::move(other.name_))
    , mass_(other.mass_)
    {
        std::swap(extra_, other.extra_);
    }
    
    // copy assignment operator
    Package& operator=(const Package& other) {
        name_ = other.name_;
        mass_ = other.mass_;
        extra_.reset(other.extra_ ? new Data(*(other.extra_)) : nullptr);
        return *this;
    }

    // move assignment operator
    Package& operator=(Package&& other) {
        name_ = std::move(other.name_);
        mass_ = other.mass_;
        std::swap(extra_, other.extra_);
        return *this;
    }

    double getMass() const {
        return mass_;
    }

    string getName() const {
        return name_;
    }

private:
    std::string name_;
    double mass_{0.0};
    std::unique_ptr<Data> extra_;
};

int main() {
    Package box {"Box", 10.0};
    std::cout << std::format("{} {}\n", box.getMass(), box.getName());

    Package tv {"TV", 200.0};
    std::cout << std::format("{} {}\n", tv.getMass(), tv.getName());

    std::cout << "copy constructor tv \n";
    Package dupTv {tv};
    std::cout << std::format("{} {}\n", dupTv.getMass(), dupTv.getName());
    
    std::cout << "move constructor tv \n";
    Package movTv {std::move(tv)};
    std::cout << std::format("{} {}\n", movTv.getMass(), movTv.getName());
    
    std::cout << "after moving tv -> movTv \n";
    std::cout << std::format("{} {}\n", tv.getMass(), tv.getName());

    return 0;                                        
}