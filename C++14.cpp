/*----------------------------------------------------------------------------------
C++14
    i) Template Enhancements
        i.i) Variable Templates
        i.ii) Template Parameter deduction
        i.iii) Generic Lambdas in Templates
    ii) Advanced Lambda Expressions
        ii.i) Explicit return types
        ii.ii) Capture by move
        ii.iii) This capture
    iii) Enhancements in Data Type
        iii.i) std::make_unique
        iii.ii) User-defined Literals (UDLs)
        iii.iii) std::shared_timed_mutex
-----------------------------------------------------------------------------------*/
#include <iostream>

// i.i)) Variable Templates: It allows to create templates for variables, rather than just 
// functions or classes. This concept allows to define constant expressions that can
// work with any type, improving generic programming and efficiency
template<typename T>
constexpr T pi = T(3.1415);  // Define pi for any type

int main() {
    auto r = 5.0;
    double area = pi<double> * r * r;  // using pi double
    return 0;
}

// i.ii)) Template Parameter Deduction: It allows compiler to deduce the types of template 
// parameters based on function arguments more intelligently
template<typename T>
auto square(T x) -> decltype(x * x) {
    return x * x;
}
template<typename T>
auto addNums(T a, T b) -> decltype(a + b) {
    return a + b;  // Return type deduced as the type of a + b
}

int main() {
    auto result = square(5);  //'T' is deduced to int
    std::cout << result << std::endl;
}

// i.iii) Generic Lambdas: This eliminates the need for complex std::function objects 
// and offers the ability to write generic usable lambda functions
auto add = [](auto a, auto b) { return a + b; };  // Generic Lambda
int main() {
    std::cout << add(5, 3) << std::endl;
    std::cout << add(3.5, 2.1) << std::endl;
    std::cout << add("Hello, ", "World!") << std::endl;
}

// ii.i) Explicit Return types for lambdas: Return type is explicitly specified by 
// -> symbol. 
auto add = [](double a, double b) -> double {
    return a + b;
};

// ii.ii) Capture-by-Move: It allows lambdas to take ownership of temporary objects,
// which is useful when dealing with large objects or containers that are expensive to copy
std::vector<int> vec = {1, 2, 3};
auto lambda = [v = std::move(vec)]() {
    std::cout << "Vector size: " << v.size() << std::endl;
};
int main() {
    lambda();
    return 0;
}

// ii.iii) Lambda with this capture: Allows to access member variables and methods of 
// enclosing class by capturing 'this' pointer
class MyClass {
    public:
        int value = 5;
        void print() {
            auto lambda = [this]() {
                std::cout << value << std::endl;
            };
            lambda();
        }
};

// iii.i) std::make_unique: A helper function to make it easier and safer to create
// unique_ptr instances. Allows to avoid potential issues with new expressions.
// Ensures that memory allocation is exception safe and reduces the risk of memory
// leaks or undefined behavior
std::unique_ptr<int> ptr(new int(10));  // Before C++14
// same as
std::unique_ptr<int> ptr = std::make_unique<int>(10);

//iii.ii) UDLs allow to define your own custom suffix for literals in the program.
// _kg is a user defined literal that converts kg to gm, making the code more
// readable and intuitive
constexpr long double operator"" _kg(long double value) {
    return value * 1000.0;  // Convert kilograms to grams
}
int main() {
    auto mass = 5.0_kg;  // 5 Kg is converted to 5000 gm
    std::cout << mass << std::endl;
}

// iii.iii) std::shared_timed_mutex: It allows multiple threads to acquire a read lock
// simultaneously but ensures exclusive access for write operations. 
#include <shared_mutex>
std::shared_timed_mutex mutex;
void read_data() {
    std::shared_lock<std::shared_timed_mutex> lock(mutex);
}
void write_data() {
    std::unique_lock<std::shared_timed_mutex> lock(mutex);
}
/*-----------------------------------------------------------------------------------
------------------------------------------------------------------------------------*/
