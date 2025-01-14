#include <iostream>
#include <type_traits>

/*----------------------------------------------------------------------------------------------------------------------
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

/*---------------------------------------------------------------------------------
SFINAE : Substitution failure is not an error
A feature in C++ template programming. When a template is being instantiated, if a
substitution of template parameters fails due to a type ismatch or an invalid
expression, the compiler does not treat this as an error. Instead, it ignores the
invalid specialization and looks for other viable specializations.
----------------------------------------------------------------------------------*/
#include <iostream>
#include <type_traits>
#include <complex>

// Function for arithmetic types
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
power(T base, int exponent) {
    T result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

// Function for types like std::complex 
template <typename T>
typename std::enable_if<!std::is_arithmetic<T>::value, T>::type
power(T base, int exponent) {
    T result = T(1);
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int main() {
    // Arithmetic types
    std::cout << "2^3 = " << power(2, 3) << std::endl;
    std::cout << "1.5^4 = " << power(1.5, 4) << std::endl;
    // Complex Numbers
    std::complex<double> c(2.0, 3.0); // 2+3i
    auto result = power(c, 2);
    std::cout << "(2+3i)^2 = " << result << std::endl;
    return 0;
}

/*----------------------------------------------------------------------------------
2^3 = 8
1.5^4 = 5.0625
(2+3i)^2 = (-5,12)
----------------------------------------------------------------------------------*/



