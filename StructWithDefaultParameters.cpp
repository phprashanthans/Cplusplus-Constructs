/* If you have a class with many constructor parameters and some of theose should
have default values, then you have several options: 
    Use constructor overloading
    Default parameters
However, Using C++20, you can define a struct with default parameters and use it.
*/
#include <iostream>
#include <string>
#include <format>

struct FooParam {
    int number = 0;
    double seed = 1.0;
    std::string name = "default name";
};
class Foo {
    public:
        explicit Foo(FooParam &&param) :
            m_number(param.number),
            m_seed(param.seed),
            m_name(std::move(param.name)) {}
    public:
        int getNumber() const {
            return m_number;
        }
        double getSeed() const {
            return m_seed;
        }
        std::string_view getName() const {
            return std::string_view(m_name);
        }
    private:
        int m_number;
        double m_seed;
        std::string m_name;
};

int main() {
    auto foo = Foo({.number = 10, .name = "custom name"});
    std::cout << std::format("number: {}, seed: {}, name: {}", foo.getNumber(), foo.getSeed(), foo.getName());
}

/* O/P: 
    number: 10, seed: 1, name: custom name
*/
