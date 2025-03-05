/*----------------------------------------------------------------------------------
C++23
1) Pattern Matching
2) Advanced Constexpr
3) Enhancements in Standard Library: std::ranges, std::span, std::string_view
4) Modules
-----------------------------------------------------------------------------------*/

// 1) Match Expression: 
// match (expression) {
//     pattern1 => statement1,
//     pattern2 => statement2,
//     additional patterns...
//     _ => default_statement  // catch-all pattern
// }
#include <iostream>
#include <variant>
#include <tuple>

int main() {
    int x = 10;
    match(x) {
        1 => std::cout << "One\n",  // Matches if x is 1
        10 => std::cout << "Ten\n",  // Matches if x is 10
        _ => std::cout << "Unknown number\n"  // Default catch-all case
    }

    std::variant<int, std::string> v = "Hello";
    match(v) {
        int i => std::cout << "Integer: " << i << '\n',
        std::string s => std::cout << "String: " << s << '\n',
        _ => std::cout << "Unknown type\n"
    }

    struct Point {
        int x, y; 
    };
    Point p = {1, 2};
    match (p) {
        Point{1, 2} => std::cout << "Point is (1, 2)\n",
        Point{x, y} => std::cout << "Point is (" << x << ", " << y << ")\n",
        _ => std::cout << "Unknown point\n"
    }

    int x = 5;
    match (x) {
        int n if (n % 2 == 0) => std::cout << n << " is even\n",
        _ => std::cout << "Not even\n"
    }

    match (x) {
        1 | 2 => std::cout << "One or Two\n",  // Matches if x is 1 or 2
        3 .. 5 => std::cout << "Between 3 and 5\n" // Matches if x is between 3 and 5
        _ => std::cout << "Other value\n"
    }

    return 0;
}

enum class Status { Success, Error, NotFound };
Status get_status() {
    return Status::Error;
}
void handle_status() {
    Status status = get_status();
    match (status) {
        Status::Success => std::cout << "Operation successful\n",
        Status::Error => std::cout << "An Error occured\n",
        Status::NotFound => std::cout << "Item not found\n",
        _ => std::cout << "Unknown status\n"
    }
}

std::tuple<int, double> get_coordinates() {
    return std::make_tuple(10, 20.5);
}
void print_coordinates() {
    auto coordinates = get_coordinates();
    match (coordinates) {
        std::tuple<int x, double y> => std::cout << "Coordinates: (" << x << ", " << y << ")\n",
        _ => std::cout << "Invalid coordinates\n"
    }
}

std::optional<int> get_value(bool valid) {
    if (valid) return 42;
    else return std::nullopt;
}
void print_value(bool valid) {
    auto valid = get_value(valid);
    match (valid) {
        int v => std::cout << "value:" << v << '\n',
        _ => std::cout << "No value\n"
    }
}

// 2) Advanced constexpr: 
// 2.1) Support for constexpr Virtual functions
struct Shape {
    virtual constexpr double area() const = 0;
};
struct Circle : public Shape {
    double radius;
    constexpr Circle(double r) : radius(r) {}
    constexpr double area() const override { return 3.14 * radius * radius; }
};
constexpr double compute_area(const Shape& shape) {
    return shape.area();
}
int main() {
    constexpr Circle circle(5.0);
    constexpr double result = compute_area(circle);  // Computed at compile time
}
// 2.2) Enhanced constexpr Lambda functions
constexpr auto multiply = [](int a, int b) { return a * b; };
int main() {
    constexpr int result = multiply(6, 7);  // Computed at compile time
}
// Use constexpr lambdas to capture by refernce or modify static variables
constexpr auto increment = [](int& x) { x++; };
int main() {
    int x = 0;
    increment(x);  // Modifies x at runtime;
}

// 2.3) Handling complex control flow in constexpr functions
constexpr int divide(int numerator, int denominator) {
    if (denominator == 0) throw std::logic_error("Divison by zero");
    return numerator/denominator;
}
int main() {
    constexpr int result = divide(10, 2);  // Computed at compile-time
}
// 2.4) constexpr and More Complex Type Traits
template <typename T>
constexpr bool is_integral_or_floating_point(T val) {
    if (constexpr (std::is_integral_v<T>)) {
        return true;
    } else if constexpr (std::is_floating_point_v<T>) {
        return false;
    }
    return false;
}
template <typename T>
constexpr int size_of_type() {
    if constexpr (std::is_integral_v<T>) {
        return sizeof(int);
    } else if constexpr (std::is_floating_point_v<T>) {
        return sizeof(double);
    }
    return 0;
}
int main() {
    constexpr bool is_integral = is_integral_or_floating_point<int>(5);
    constexpr bool is_floating = is_integral_or_floating_point<float>(3.14);
    constexpr int int_size = size_of_type<int>();
    constexpr int double_size = size_of_type<double>();
}

// 3) Enhancements in Standard Library
// std::range - New algorithms are introduced, and several existing are enhanced

#include <ranges>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    // Using the ranges to double values and then filter odd numbers
    auto doubled_and_even = numbers | std::ranges::views::transform([](int n) {
        return n * 2;
    }) | std::ranges::views::filter([](int n) {
        return n % 2 == 0;
    });
    for (int n : doubled_and_even) {
        std::cout << n << " "; 
    }
    return 0;
}

// String handling enhancements
// std::string_view now supports efficient slicing and searching for substrings
#include <string_view>
#include <iostream>

int main() {
    std::string_view view = "Hello World!";
    // View a substring without actually copying the data
    std::cout << view.substr(0, 5) << "\n";
}

// 4) Modules: 

// Module Interface: Specifies what functionality is available to external code
#include <format>
#include <iostream>

int main() {
    int age = 30;
    std::string name = "John";
    std::cout << std::format("My name is {}, and I am {} years old.", name, age) << std::endl;
}
// Module Implementation: REsponsible for defining how that functionality works
// (myModule.cpp)
module myModule;  // Define implementation of the 'myModule'
void greet() {
    std::cout << "Hello, Modules!" << std::endl;  // Actual implementation of greet()
}

// Import the 'myModule' module into the source file
import myModule;
