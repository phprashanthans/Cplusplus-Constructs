#include <iostream>

class Foo {
    public:
        void bar() const & {
            std::cout << "Normal Value" << std::endl;
        }
        void bar() && {
            std::cout << "Temporary Value" << std::endl;
        }
};

int main() {
    auto foo = Foo{};
    foo.bar();   // Calls the first one : Normal Value
    Foo{}.bar(); // Calls the second one : Temporary Value
    return 0;
}
