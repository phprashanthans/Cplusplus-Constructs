/* Variadic Templates: It allows creating a function or class that accepts any
number of parameters. The feature works well for classes like std::variant and
std::tuple, or even functions like std::print. 
*/

#include <iostream>
#include <concepts>

template<typename ...Args>
requires ((std::floating_point<Args> || std::integral<Args>) && ...)
auto sum(Args ...args) {
    return (args + ...);
}

int main() {
    std::cout << sum(1.1, 10.f, 2044, true) << std::endl;
    return 0;
}

/* O/P: 
    2056.1
*/
