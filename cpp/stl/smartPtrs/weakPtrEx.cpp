#include <memory>
#include <iostream>

struct Player
{
  //std::shared_ptr<Player> companion;
  // To avoid circular dependencies and to call destructor correctly..
  // ref: https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c
  std::weak_ptr<Player> companion;
  ~Player() { std::cout << "~Player\n"; }
};

int main() {
    //-----------
    // Ex1
    {
    std::weak_ptr<int> wp;
    {
        std::shared_ptr<int> sp = std::make_shared<int>(53);
        wp = sp;
 
        auto p = wp.lock();
        if (p) {
            std::cout << "still connected" << "\n";
        }
        else {
            std::cout << "null" << "\n";
        }
    }
 
    auto p = wp.lock();
    if (p) {
        std::cout << "still connected" << "\n";
    }
    else {
        std::cout << "null" << "\n";
    }
    std::cout << wp.expired() << "\n"; // 1 (true)
    }
    
    //-------------
    // Ex2
    {
        std::shared_ptr<Player> jasmine = std::make_shared<Player>();
        std::shared_ptr<Player> albert  = std::make_shared<Player>();

        jasmine->companion = albert; // (1)
        albert->companion  = jasmine; // (2)
    }

    return 0;
}