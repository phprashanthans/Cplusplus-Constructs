/*-----------------------------------------------------------------------------------
Variants as an alternative to inheritance and virtual functions
//Drawbacks:
It is all cool when you know ALL of the types that will ever be used AND
when you don't mind storing the extra bytes in every single instance because
it requires the full storage of the largest object even if you never use it.
You save not storing the v-table pointer at the cost of dozens of hundreds of
extra bytes because you are using the footprint of your largest object.
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>

struct Circle {
    void draw() const {
        std::cout << "Draw Circle" << std::endl;
    }
};

struct Rectangle {
    void draw() const {
        std::cout << "Draw Rectangle" << std::endl;
    }
};

using Shape = std::variant<Circle, Rectangle>;

int main() {
    std::vector<Shape> shapes;
    shapes.push_back(Circle());
    shapes.push_back(Rectangle());

    for (auto& shape : shapes) {
        std::visit([](auto& s) {
            s.draw();
        }, shape);
    }
    return 0;
}



/*----------- Output --------------------
Draw Circle
Draw Rectangle
----------------------------------------*/
