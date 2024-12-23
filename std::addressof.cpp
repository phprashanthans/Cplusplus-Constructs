/*---------------------------------------------------------------------------------
std::addressof ==> There might be exceptions, such as overloading the unary operator &
In that case, the returned value might be surprising. To handle this safely, use
std::addressof which always returns the actual address of the object, regardless of 
operator overloading
----------------------------------------------------------------------------------*/
#include <iostream>
#include <memory>  // For std::addressof

struct NormalStruct {
    int value;
};

class CustomAddress {
    public:
        char padding = 0;
        int value;
    CustomAddress(int val) : value(val) {}
    int* operator&() {
        std::cout << "Custom Operator& called!" << std::endl;
        return &(this->value); 
    }
};

int main() {
    NormalStruct ns{42};
    std::cout << "NormalStruct Address using &: " << &ns << std::endl;
    std::cout << "NormalStruct Address using addressof: " << std::addressof(ns) << std::endl;

    CustomAddress obj(100);
    int* customAddr = &obj;
    std::cout << "Address from custom operator&" << customAddr << std::endl;
    CustomAddress* realAddr = std::addressof(obj);
    std::cout << "Actual Address using addressof" << customAddr << std::endl;
    return 0;
}
