/*---------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <type_traits>

// Primary template
template<typename T>
class Printer {
    public:
        void print(const T& value) {
            std::cout << "Generic Printer: " << value << std::endl;
        }
};
// Specialization for int
template<>
class Printer<int> {
    public:
        void print(const int& value) {
            std::cout << "Integer Printer: " << value << "(specialized handling)" << std::endl; 
        }
};
// Specialization for string
template<>
class Printer<std::string> {
    public:
        void print(const std::string& value) {
            std::cout << "String Printer: " << value << "(specialized handling)" << std::endl; 
        }
};
// Helper function
template <typename T>
void print_value(const T& value) {
    Printer<T> printer;
    printer.print(value);
}

int main() {
    double d = 3.14;
    print_value(d);
    int i = 42;
    print_value(i);
    std::string str = "Hello Naruto";
    print_value(str);
    return 0;
}
