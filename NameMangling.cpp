/*---------------------------------------------------------------------------------
Name Mangling: C++ supports function overloading i.e. there can be more than one 
function with the same name but, different parameters. How does the C++ compiler
distinguishes between different functions when it generates object code ? It changes 
name by adding information about arguments. This technique is called name mangling. 
In C, the names are not mangled as function overloading is not supported. To force 
a C++ compiler to produce a C function and not do name mangling, use the extern "C"
----------------------------------------------------------------------------------*/

#include <iostream>

// Expose C++ functions as C-compatible using extern "C"
extern "C" {
    void add_numbers(int a, int b); // C-compatible function
    void greet(const char* name);  // C-compatible function
}

// Function implementations exposed as C-compatible
void add_numbers(int a, int b) {
    std::cout << "The sum of integers " << a << " and " << b << " is " << (a+b) << std::endl;
}
void greet(const char* name) {
    std::cout << "Hello " << name <<
    "! This is a C++ function exposed as C-compatible" << std::endl;
}

// Overloaded function for double parameters. C++ only, not exposed to C.
void add_numbers(double a, double b) {
    std::cout << "The sum of doubles " << a << " and " << b << " is " << (a+b) << std::endl;
}

int main() {
    add_numbers(3, 7);
    add_numbers(3.5, 7.2);
    greet("Naruto Uzumaki");
    return 0;
}
