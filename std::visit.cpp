// Visitor Pattern Implementation without cross dependency, virtual functions and spaghetti code

#include <iostream>
#include <vector>
#include <variant>

struct A { int i = 43; };
struct B { float f = 3.14F; };
struct C { std::string s = "str"; };

struct Print {
    void operator()(A value) const { std::cout << "int:" << value.i << "\n"; }
    void operator()(B value) const { std::cout << "float:" << value.f << "\n"; }
    void operator()(C value) const { std::cout << "string:" << value.s << "\n"; }
};

// std::variant : used to store multiple data types in a single variable.

int main() {
    std::variant<A, B, C> v;
    v = A();
    std::visit(Print{}, v);  // int : 43
    v = B();
    std::visit(Print{}, v);  // float : 3.14
    v = C();
    std::visit(Print{}, v);  // string : str
}

// std::visit with return values

#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <numeric>

struct Circle {
    double radius;
};
struct Square {
    double side;
};
struct Triangle {
    double base;
    double height;
};
struct AreaVisitor {
    double operator()(const Circle& circle) const {
        return 3.14f * circle.radius * circle.radius;
    }
    double operator()(const Square& square) const {
        return square.side * square.side;
    }
    double operator()(const Triangle& triangle) const {
        return 0.5 * triangle.base * triangle.height;
    }
};

int main() {
    std::vector<std::variant<Circle, Square, Triangle>> shapes = {Circle{10.2}, Triangle{10.6, 5.0},
    Square{2.1}, Circle{5.2}, Square{5.9}, Triangle{0.6, 5.0}};
    // Utilize std::visit to calculate area depending on type
    const auto area = std::accumulate(shapes.cbegin(), shapes.cend(), 0.0,
    [](auto res, const auto& shape) {
        return res + std::visit(AreaVisitor{}, shape);
    });
    std::cout << "Total Area:" << area << std::endl;
    return 0; 
}
