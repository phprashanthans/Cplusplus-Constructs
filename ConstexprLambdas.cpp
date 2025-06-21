/*-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------*/
#include <iostream>

int nonConstexprFunction() {
    return 1;
}

constexpr int constexprFunction() {
    return 1;
}

// operator() in a lambda is implicitly constexpr, if
// it satisfies all constexpr function requirements
auto lambda = []() {
    return 1;
};

int main() {
    constexpr auto a = nonConstexprFunction();  // ERROR
    constexpr auto b = constexprFunction();     // OK
    constexpr auto c = lambda();                // OK
    return 0;
}

/*----------- Output --------------------
----------------------------------------*/
