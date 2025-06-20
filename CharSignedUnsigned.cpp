/***********************************************************************************
In C++, char, signed char, and unsigned char are considered distinct types.
Even though char can behave like either a signed char or an unsigned char depending
on compiler, the typeid operator differentiates between them.
The typeid operator returns a std::type_info, which uniquely identifies
a type. 
************************************************************************************/
#include <iostream>

int main() {
    char a{};
    signed char b{};
    unsigned char c{};

    if (typeid(a) == typeid(b)) {
        std::cout << "typeid(char) == typeid(signed char)" << std::endl;
    } else if (typeid(a) == typeid(c)) {
        std::cout << "typeid(char) == typeid(unsigned char)" << std::endl;
    } else {
        std::cout << "No typeid same" << std::endl;
    }
    return 0;
}

/*******************
O/P: No typeid same"
*******************/
