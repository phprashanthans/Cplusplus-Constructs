/* std::variant is a type safe union introduced in C++17 that allows a variable 
which can hold multiple types and allocates the memory for largest type. It's 
great tool for flexible data handling without compromising safety.
In std::variant, only one type is active at a time, eliminating the need for manual type
tracking. A common use is when a function might return different types depending on the
situation. 
std::holds_alternative<T>() checks which type is currently held, while std::visit() helps
to apply operations based on active type. Accessing the wrong type will throw a 
std::bad_variant_access exception.
*/
#include <iostream>
#include <variant>

int main() {
    std::variant<int, float, std::string> myVariant;
    myVariant = 10;
    std::cout << "int: " <<  std::get<int>(myVariant) << ", " << std::get<0>(myVariant) << std::endl;

    myVariant = 3.14f;
    try{
        std::cout << "int: " << std::get<int>(myVariant);
    } catch(const std::bad_variant_access& e) {
        std::cout << "Exception Caught: "<< e.what() << std::endl;
    }
    if (std::holds_alternative<float>(myVariant)) {
        std::cout << "float: " << std::get<float>(myVariant) << std::endl;
    }
    auto visitor = [](auto&& arg) {
        std::cout << "In Visitor: " << arg << std::endl; 
    };
    myVariant = "Hello";
    std::visit(visitor, myVariant);
    return 0;
}
