/*---------------------------------------------------------------------------------
std::move is merely a template function. It's nothing but a static_cast to an rvalue
reference type. It doesn't move anything by itself. It marks an object to be movable
by indicating, "I no longer need this value here". It signals the object to be passed
to an rvalue reference such that they should transfer ownership of resources rather
than copying them.
std::string greeting("Hello World!");
std::string&& msg = greeting;  // XXXX
std::string&& msg = std::move(greeting);  \/\/
1) greeting is a named object, so its value category as an expression is an lvalue.
According to binding rule, an rvalue reference cannot be bound to an lvalue.
2) By applying std::move, we produce an expression whose value category is an xvalue
i.e. an expiring value. This transformation allows greeting to bind to an rvalue 
reference.
3) After this transformation, std::move(greeting) exhibits the following characterstics:
Type: std::string&&
Value category: xvalue
Note:- msg is an rvalue reference and is just an alias to the existing object greeting.
No actual move operations are performed here.  
----------------------------------------------------------------------------------*/
#include <iostream>

class Thing {
    public:
        Thing() {
            std::cout << "Thing() " << this << '\n';
        }
        Thing(const Thing&) {
            std::cout << "Thing(const Thing&)\n";
        }
        Thing& operator=(const Thing&) {
            std::cout << "operaor=(const Thing&)\n";
            return *this;
        }
        Thing(Thing&&) noexcept {
            std::cout << "Thing(Thing&&)\n";
        }
        Thing& operator=(Thing&&) noexcept {
            std::cout << "operator=(Thing&&)\n";
            return *this;
        }
        ~Thing() {
            std::cout << "~Thing()" << this << '\n';
        }
};
static Thing func() {
    Thing temp;
    //.....
    return temp;  // GOOD: Do this
    // return std::move(temp);   //BAD: don't do this;
}

int main() {
    Thing t = func();
    return 0;
}

/*----------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
