/*----------------------------------------------------------------------------------
C++11
1) Smart Pointers
2) Lambda Expressions
3) Advanced Types: auto, decltype, range-based loops
4) Constexpr expressions
-----------------------------------------------------------------------------------*/

// 1) Smart Pointers
// unique_ptr: It enforces exclusive ownership of object it points to. That means
// that only one unique_ptr can own the object at any time, and ownership can be moved/
// transferred, but not copied. No other pointer can share the ownership of the resource.

// shared_ptr: It represents shared ownership of a dynamically allocated object.
// Multiple shared_ptr instances can point to the same object, and the object is 
// automatically destroyed when the last shared_ptr that owns it is destroyed or reset.
// The feature is useful when you have multiple parts of program need to access the 
// same resource but should not be responsible for its destruction individually.

// weak_ptr: Provides an non-owning reference to an object managed by shared_ptr.
// The main purpose is to prevent circular reference that could lead to memory leaks.
// A weak_ptr doesn't contribute to reference count of object, meaning it doesn't 
// prevent the object from being deleted. 

#include <iostream>
#include <memory>
class MyClass {
    public:
        void great() const {
            std::cout << "Hello World!" << std::endl;
        }
};
int main() {
    std::unique_ptr<MyClass> ptr1 = std::make_unique<MyClass>();  // ptr1 owns MyClass
    ptr1->great();

    // Ownership can be transferred, but not copied
    std::unique_ptr<MyClass> ptr2 = std::move(ptr1);  // Ownership transferred to ptr2

    // ptr1 is now nullptr and cannot be used
    ptr2->great();  // ptr2 owns MyClass

    std::shared_ptr<MyClass> ptr3 = std::make_shared<MyClass>();  // ptr3 owns MyClass
    std::shared_ptr<MyClass> ptr4 = ptr3;  // ptr4 shares ownership

    std::weak_ptr<MyClass> ptr5 = ptr3;  // weak_ptr observes the object

    ptr3->great();
    ptr4->great();

    return 0;  
    // When ptr2 goes out of scope, MyClass is destroyed automatically.
    // When both ptr3 and ptr4 ggo out of scope, MyClass is destroyed automatically
}

// 2) Lambda Expressions: [capture](parameter_list) -> return_type { body }

#include <iostream>
int main() {
    int a = 5, b = 10, c = 15;

    // Define a lambda to add two integers
    auto addByValue = [=]() -> int {  // Captures 'a' and 'b' by value
        return a + b;
    };

    auto addByReference = [&]() -> int {  // Captures 'a' and 'b' by reference
        a = 100;  // Modifies 'a' in outer scope
        return a + b;
    };

    auto add = [a, &b]() -> double {
        std::cout << "Sum: " << a + b << std::endl;  // 'a' is captured by value, 'b' by reference
        b = 20;  // Modifies the original 'b'
    };

    auto addDefault = [&, c]() {  // Default capture by reference, except for 'c' captured by value
        std::cout << "Sum: " << a + b + c<< std::endl;  // 'a' and 'b' is captured by reference, 'c' by reference
        a = 100;  // Modifies the original 'a'
        b = 200;  // Modifies the original 'b'
    };

    // Call the lambda
    add();
    addByValue();
    addByReference();
    addDefault();
    return 0;
}

// 3) Advanced Type : auto, decltype, range-based for loops
// It helps compiler automatically deduce the types. auto keyword allows the compiler 
// to deduce the type from the type of its initializer, reducing the need of explicit 
// type declarations.
// decltype is used to deduce the type of an expression without evavluating it, unlike auto
// The decltype doesn't evaluate the expression; it simply inspects the type.
// Range based for loops to iterate over arrays, vectors and other iterable types

#include <iostream>
#include <vector>
#include <map>

int func() {
    return 10;
}

int main() {
    auto x = 5;     // x is deduced as int
    auto y = 3.14;  // y is deduced as double
    std::vector<int> vec = {1, 2, 3, 4};
    // Using auto to deduce the iterator type
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }

    // Using decltype to deduce the type of sum of 'x' and 'y'
    decltype(x + y) result = x + y;  // result is deduced as double
    // Using decltype to get the return type of func
    decltype(func()) x = func();  // 'x' is deduced as int
    // Using both 'auto' and 'decltype' 
    auto it = vec.begin();        // Auto deduces iterator type
    decltype(*it) value = *it;    // Decltype deduces the value

    // Range based for loop to iderate through the vector
    for (auto num : vec) {
        std::cout << num << " ";
    }
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    // Range based loops over map
    for (const auto& pair : m) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    return 0;
}

// 4) Constexpr expressions
// Constexpr function is a function whose return value is computed at compile-time if 
// all of it's arguments are constant expressions. 
constexpr int square_func(int x) {
    return x * x;
}
// Complex operations
constexpr int factorial(int n) {
    return (n == 0) ? 1 : n * factorial(n - 1);
}
// Dynamic Memory Allocation
constexpr int* create_array(int size) {
    return new int[size];
}
// Constexpr lambdas
constexpr auto square_lambda = [](int x) { return x * x; };
// if constexpr
constexpr int max(int a, int b) {
    if constexpr (a > b) return a;
    else return b;
}
/*-----------------------------------------------------------------------------------
------------------------------------------------------------------------------------*/
