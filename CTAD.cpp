/*---------------------------------------------------------------------------------
Since C++17, the compiler can automatically determine the template parameter of a 
class based on initialization expression. This feature is called class template
argument deduction (CTAD)
Benefit is that you can skip explicitly specifying the template parameter when 
initializing a class i.e. auto a = std::pair{1,2} instead of std::pair<int, int>
THis can only happen when the types in the constructor and template parameters 
match. In complex cases, you need to guide the compiler. 
----------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

template <typename T>
class Container {
    public:
        Container(std::initializer_list<T> data) : m_data(data) {
        }
        template<std::input_iterator I>
        Container(I begin, I end) : m_data(begin, end) {
        }
        T at(std::size_t index) const {
            return m_data.at(index);
        }
    private:
        std::vector<T> m_data;
};

template<std::input_iterator I>
Container(I begin, I end) -> Container<typename std::iterator_traits<I>::value_type>;

int main() {
    {
        auto container = Container({1, 2, 3});
        std::cout << container.at(0) << std::endl;
    }
    {
        std::vector v = {1.1, 2.2, 3.3};
        // Compiler error: Compiler cannot deduce the template parameter in such case.
        // The ierator type doesn't directly match with container type
        auto container = Container(v.cbegin(), v.end());
        std::cout << container.at(0) << std::endl;
    }
    return 0;
}

/*----------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
