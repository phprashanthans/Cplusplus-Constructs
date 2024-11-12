/* std::declval is used in metaprogramming to convert a type parameter into a reference
It can be especially useful when a type doesn't have a default constructor. The 
resulting reference can be used further, for example, to deduce the return type of
a member function. 
std::decltype is used to detect the type of an expression. Moreover, one can specify a 
return type as decltype(auto) for perfect forwarding.
*/

#include <iostream>

class Foo {
    public:
        explicit Foo(char) {}
    public:
        int value() const {
            return 10;
        }
};

template <typename T> 
class Sum {
    public:
        // Calculate type returned by the function 'T::Value()'
        using Value = decltype(std::declval<T>().value());
    public:
        Value result() const {
            return m_value;
        }
        void add(const T& value) {
            m_value += value.value();
        }
    private:
        Value m_value;
};

int main() {
    auto sum = Sum<Foo>();
    sum.add(Foo('a'));
    sum.add(Foo('b'));
    std::cout << sum.result() << std::endl;
    return 0;
}

/* O/P: 
    20
*/
