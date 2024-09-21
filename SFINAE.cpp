#include <iostream>
#include <type_traits>

/*
std::enable_if<std::is_arithmetic<T>::value, T>::type: This is a SFINAE (Substitution Failure Is Not An Error) technique. 
It checks if T is an arithmetic type (like int, float, etc.). If T is arithmetic, the function will be instantiated; 
otherwise, it will not be available.
std::is_arithmetic<T>::value evaluates to true for arithmetic types.
If the condition is true, the type of the function is T, allowing the addition operation.
*/
template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
MathOperation(T a, T b) {
    return (a + b);
}

int main() {
    constexpr int x{10};
    constexpr int y{2};
    auto res = MathOperation(x, y);
    std::cout << "Operation Result:" << res << std::endl;
    return 0;
}
