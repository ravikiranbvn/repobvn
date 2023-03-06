#include <iostream>
#include <memory>

class Rectangle {
public:
    Rectangle(int w, int h) : width(w), height(h) {}
    ~Rectangle() { std::cout << "Rectangle destructor" << std::endl; }
    int getArea() { return width * height; }
private:
    int width;
    int height;
};

int main(){
    // wrong way of using shared_ptr:
    /*Rectangle* rectp = new Rectangle(5, 3);
    std::shared_ptr<Rectangle> rectsp1(rectp);
    std::shared_ptr<Rectangle> rectsp2(rectp);
    //rectsp1.reset(rectp);
    std::cout << rectsp1->getArea() << std::endl;
    return 0;*/
    
    // Fix:
    std::shared_ptr<Rectangle> rectsp1 = std::make_shared<Rectangle>(5,3);
    std::shared_ptr<Rectangle> rectsp2 = std::make_shared<Rectangle>(5,3);
    std::cout << rectsp1->getArea() << std::endl;
    return 0;
}
