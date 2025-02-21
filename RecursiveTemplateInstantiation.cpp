/*----------------------------------------------------------------------------------
Recursive Template Instantiation: A technique in C++ template metaprogramming that
enables compile-time computations. Unlike traditional runtime recursion, where 
function calls are executed during program execution, recursive template instatiation 
unfolds entirely at compile time.

Since C++11, we can use constexpr functions which is a better way compared to template
instantiation as it would generate more template instances
-----------------------------------------------------------------------------------*/
#include <iostream>

template <int N>
class Factorial {
    public:
        static constexpr int value = N * Factorial<N-1>::value;
};
template<>
class Factorial<0> {
    public:
        static constexpr int value = 1;
};

constexpr int factorial(int n) {
    return (n != 0) ? (n * factorial(n-1)) : 1;
}

int main() {
    std::cout << "Factorial of 5: " << Factorial<5>::value << std::endl;
    constexpr int res = factorial(5);
    std::cout << "Factorial of 5: " << res << std::endl;
    return 0;
}
/*---------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
