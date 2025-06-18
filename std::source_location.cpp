/*-----------------------------------------------------------------------------------
std::source_location is a C++20 feature. It is a class that represents information
about a specific point in the source code, such as filename, line number, column 
number, and function name where an expression or function is defined or called.
file_name()
line()
column()
function_name()
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <source_location>

class WhichCtor {
    public:
        WhichCtor(int a, int b, int c) {
            std::cout << std::source_location::current().function_name() << std::endl;
        }
        WhichCtor(std::initializer_list<int> args) {
            std::cout << std::source_location::current().function_name() << std::endl;
        }
};

int main() {
    WhichCtor(0, 1, 2);
    WhichCtor({0, 1, 2});
    return 0;
}

