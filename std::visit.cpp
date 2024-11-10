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
