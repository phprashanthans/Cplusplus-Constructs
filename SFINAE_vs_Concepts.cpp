/*---------------------------------------------------------------------------------
Concepts: A C++20 feature that allows to specify constraints on template parameters.
It provides a more expressive and readable way to describe requirements on types used
in templates. 
Concepts can be thought of as predicates that check if a type satisfies certain 
conditions. For example, we can define a concept that ensures a type has a particular
member function, or that it is an arithmetic type.
----------------------------------------------------------------------------------*/

1) ---------------USING SFINAE----------------------
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

2) ---------------USING CONCEPTS----------------------
#include <iostream>
#include <complex>
#include <concepts>

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T>
T Power(T base, int exponent) {
    T result = 1;
    for(int i=0; i<exponent; i++){
        result *= base;
    }
    return result;
}

template <typename T>
concept Complex = requires(T t) {
    std::is_same_v<T, std::complex<typename T::value_type>>;
};
template <Complex T>
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
    std::cout << "2^3 = " << Power(2, 3) << std::endl;
    std::cout << "1.5^4 = " << Power(1.5, 4) << std::endl;
    // Complex Numbers
    std::complex<double> c(2.0, 3.0); // 2+3i
    auto result = power(c, 2);
    std::cout << "(2+3i)^2 = " << result << std::endl;
    return 0;
}
