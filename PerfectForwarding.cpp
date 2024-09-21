/* Perfect Forwarding:
    Forwards arguments to another function while preserving their value category without 
    code duplication. Otherwise, separate functions need to be created to handle 
    lvalues and rvalues, leading to unnecessary duplication.
    When writing templates, we often don't know the exact type or value category of 
    argument until compile time. Perfect forwarding is helpful here.
*/
#include <iostream>

void func_helper(int& arg) { std::cout << "LValue\n"; }
void func_helper(int&& arg) { std::cout << "RValue\n"; }

template<typename T>
void func(T&& arg) {
    // Forward argument to the func_helper
    func_helper(std::forward<T>(arg));
}

int main() {
    int x = 5;
    func(x);
    func(10);
    return 0;
}
