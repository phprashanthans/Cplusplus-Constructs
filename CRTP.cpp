/*-------------------------------------------------------------------------------/
CRTP: Curiously Recurring Template Pattern
It involves a class template inheriting from another class template that takes
the derived class as a template parameter. This allows static polymorphism which
can be used to implement compile time polymorphishm
/-------------------------------------------------------------------------------*/

#include <iostream>

template<typename Derived>
class Base {
    public:
        void inheritance() {
            // Call a method that will be defined in Derived
            static_cast<Derived*>(this)->implementation();
        }
};

class Derived : public Base<Derived> {
    public:
        void implementation() {
            // Implementation of the method
        }
};
int main() {
    return 0;
}

/*-------------Output:----------------/
/------------------------------------*/
