/*-----------------------------------------------------------------------------------
Calling a Method on a NUll Pointer Doesn't always cause a crash
Invoking a method on a null pointer is definitely a bug - but surprisingly, it doesn't 
always lead to memory corruption or a crash.
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <memory>

class Foo {
    public:
        void foo1() {
            std::cout << "Called foo1" << std::endl;
        }
        void foo2() {
            std::cout << "Called foo2" << std::endl;
        }
};

int main() {
    Foo* foo = nullptr;
    foo->foo1();
    foo->foo2();
    // Why does the above code works fine on nullptr
    // It's because of how method calls are handled internally in C++
    // When you invoke a method, the function is actually independent
    // of the object - it receives the object's address as an implicit
    // first parameter (the this pointer). If you call a method on a 
    // null pointer, the method still gets invoked - but with this == nullptr
    
    // As long as the method doesn't access or modify any member variables,
    // no memory is dereferenced, and the undefined behavior might go unnoticed.

    return 0;
}

/*----------- Output --------------------
Called foo1
Called foo2
----------------------------------------*/
