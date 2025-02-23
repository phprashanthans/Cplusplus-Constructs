/*----------------------------------------------------------------------------------
C++17
i) Structured Bindings
ii) std::optional and std::variant
iii) Advanced constexpr and std::string_view
iv) Inline Variable Definition
-----------------------------------------------------------------------------------*/

#include <iostream>
// i) Structured Bindings: Allows to decompose complex types such as tuples, pairs, 
// arrays and user defined structures into individual variables in simple manner.
// auto [var1, var2, ...] = expression
// The expression must return a tuple-like type
std::pair<int, std::string> getPair() {
    return {42, "Answer"};
}
struct Point {
    int x, y;
};
int main() {
    // With Pairs
    auto [x, y] = getPair();
    std::cout << "x:" << x << ", y:" << y << std::endl;

    // With Arrays
    int arr[3] = {1, 2, 3};
    auto [a, b, c] = arr;  // Unpacks the array

    // With User-defined types
    Point p = {10, 20};
    auto [a,b] = p;
    std::cout << "x:" << a << ", y:" << b << std::endl;

    // With Refernces and const qualifiers
    const auto& [x,y] = getPair(); // x and y are bound as const reference and cannot be modified
    std::cout << "x:" << x << ", y:" << y << std::endl;
}

// ii) std::optional : A wrapper that may or may not contain a value of given type. It is 
// particularly useful for situations where a value might be absent or undefined, replacing
// older methods of representing optionality, such as using null pointer or sentinel values like -1
// std::variant : A type-safe union that can hold one of the several specified types, but only one
// at a time. Unions provide no type-safety, variants provide methods to safely check and retrieve value

std::optional<int> findValue(bool found) {
    if (found) {
        return 42;  // Returns a value
    } else {
        return std::nullopt;  // Returns no value
    }
}
int main() {
    auto result = findValue(true);
    if (result) {
        // Dereference to get the value
        std::cout << "Found value: " << *result << std::endl;
    } else {
        std::cout << "No value found" << std::endl;
    }
}

std::variant<int, double, std::string> v = 10;
int main() {
    if (std::holds_alternative<int>(v)) {
        std::cout << "Integer value: " << std::get<int>(v) << std::endl;
    }
    v = "Hello World!";
    if (std::holds_alternative<std::string>(v)) {
        std::cout << "String value: " << std::get<std::string>(v) << std::endl;
    }
}

// iii) Advanced constexpr: C++11 were limited to simple expression that could be evaluated at
// compile time. C++17 expanded this capability, allowing more complex computations in constexpr
// including dynamic memory allocation(new), control flow(if, for) and complex logic.
constexpr int factorial(int n) {
    if (n <= 1 ) return 1;
    return n * factorial(n-1);
}
int main() {
    constexpr int val = factorial(5);  // Compute at compile-time
    std::cout << "Factorial of 5 is:" << val << std::endl;
}
// std::string_view: It is non-owning, lightweight view of a string. It allows you to efficiently 
// access substrings without have to copy data.
void printStringView(std::string_view str) {
    std::cout << "String: " << str << std::endl;
}
int main() {
    std::string str = "Hello World!";
    printStringView(str);  // No copy occurs
}

// iv) Inline Variable Definition: Prior to C++17, variables with external linkage had to be
// declared in .h files using extern keyword and definitions were placed in .cpp files. In 
// C++17, it allows variables to be defined inline, which means they can be defined in header
// files without violating one-definition rule.
inline int global_variable = 42;  // In header file, no need for 'extern' in source file

/*-----------------------------------------------------------------------------------
------------------------------------------------------------------------------------*/
