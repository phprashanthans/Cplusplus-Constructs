#include <iostream>
#include <type_traits>

/*----------------------------------------------------------------------------------------------------------------------
SFINAE:
std::enable_if<std::is_arithmetic<T>::value, T>::type: This is a SFINAE (Substitution Failure Is Not An Error) technique. 
It checks if T is an arithmetic type (like int, float, etc.). If T is arithmetic, the function will be instantiated; 
otherwise, it will not be available.
std::is_arithmetic<T>::value evaluates to true for arithmetic types.
If the condition is true, the type of the function is T, allowing the addition operation.
*/----------------------------------------------------------------------------------------------------------------------
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
MathOperation(T a, T b) {
    return (a + b);
}

int main() {
    constexpr int x{10};
    constexpr int y{2};
    auto res = MathOperation(x, y);
    std::cout << MathOperation("a", "b");   // Compilation Error
    std::cout << "Operation Result:" << res << std::endl;
    return 0;
}

/*---------------------------------------------------------------------------------
Concepts: A C++20 feature that allows to specify constraints on template parameters.
It provides a more expressive and readable way to describe requirements on types used
in templates. 
Concepts can be thought of as predicates that check if a type satisfies certain 
conditions. For example, we can define a concept that ensures a type has a particular
member function, or that it is an arithmetic type.
----------------------------------------------------------------------------------*/
#include <concepts>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
T MathOperation(T a, T b) {
    return (a + b);
}

int main() {
    constexpr int x{10};
    constexpr int y{2};
    auto res = MathOperation(x, y);
    std::cout << MathOperation("a", "b");   // Compilation Error
    std::cout << "Operation Result:" << res << std::endl;
    return 0;
}

/*---------------------------------------------------------------------------------/
SFINAE: Substitution Failure Is Not An Error
A principle that allows for template specialization based on whether a substitution
of template parameters is valid or not. It helps in creating more flexible and 
adaptive template code.
/---------------------------------------------------------------------------------*/

#include <iostream>

template <typename T>
auto func(T value) -> decltype(value.someMethod(), void()) {
    // Implementation for types with 'someMethod'
}
template <typename T>
void func(T value, ...) {
    // Fallback implementation for other types
}
