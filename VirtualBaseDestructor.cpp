/*----------------------------------------------------------------------------------
If you are working with inheritance and polymorphism in C++, you must always declare
the destructor of the base class as virtual.
Importance: 
When you create an object of a derived class, the constructors are called
in order - from the base class to the derived class. StraightForward. 
When the object is destroyed, the destructors are called in reverse order - starting
from derived class back to the base. 
Problem:
If you are having a base class pointer pointing to a derived class object, and you
delete the object through base class pointer, the destructor of base class is called
but not the derived class constructor. This leads to incomplete destruction, leaving
resources allocated by the derived class hanging. 
Solution:
Declare the base class destructor as virtual. By doing so, the compiler ensures that
when you delete an object through a base class pointer, it looks up for the 
destructor in the virtual table. This guarantees the correct destructor is called 
for the derived class, followed by the base class destructor - proper cleanup
-----------------------------------------------------------------------------------*/
#include <iostream>

class Base {
    public:
        virtual ~Base() {
            std::cout << "Base Destructor\n";
        }
};
class Derived : public Base {
    public:
        ~Derived() override {
            std::cout << "Derived Destructor\n";
        }
};

int main() {
    Base* obj = new Derived();
    delete obj;    // Calls ~Derived() first, then ~Base()
    return 0;
}
/*---------------------------------------------------------------------------------
Derived Destructor
Base Destructor
----------------------------------------------------------------------------------*/
