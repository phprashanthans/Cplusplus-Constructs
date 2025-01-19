/* Perfect Forwarding:
    Perfect forwarding ensures that the argument is passed along to another function exactly as it
    was received—whether as an lvalue or rvalue. This is achieved by using std::forward, a
    standard library utility introduced in C++11
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

-----------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <utility>
template <typename T>
void push_back_value(std::vector<T>& v, T&& value) {
    v.push_back(std::forward<T>(value)); // Forward the value as it was received
}

int main() {
    std::vector<int> vec;
    int x = 10;
    // Forward an lvalue
    push_back_value(vec, x);
    // Forward an rvalue
    push_back_value(vec, 20);
    for (const auto& item : vec) {
        std::cout << item << " "; // Output: 10 20
    }
}
