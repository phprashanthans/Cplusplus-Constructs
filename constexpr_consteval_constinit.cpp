/*-----------------------------------------------------------------------------------
constexpr, consteval, constinit

constexpr: 
Applicable to variables, functions and class methods
With variable, it marks it as a constant compile-time value. That makes
it possible to use such a constant in template parameter specialization or in
any other compile time expressions. 
For functions and member methods, constexpr allows them to be invoked at
both compile-time and runtime. 
constexpr constructor facilitates creation of an object at compile-time
When the method will be called highly depends on the context: if parameters
are compile time values, like literals or constexpr variables, then 
execution is done at complile time. But if one of the parameters is an 
ordinary variable or the result of some non-constexpr function, then the 
constexpr function is executed at runtime.

consteval:
To enable function calls only at compile time, C++ offers another qualifier - consteval
Invoking such function at runtime will cause a compilation error. If the 
constructor of an object is marked as consteval, this object might be created only 
at compile time.

constinit: 
It might only be used for variables. It doesn;t make a variable constant
instead, it forces the variable to be initialized with a value known at
compile time, for example, with a literal or the result of a consteval/constexpr 
function. This is needed because of the unspecified order of static and
thread-local variable initialization. The standard states that constinit
variables are initialized before the run of main and even before the 
initialization of ordinary static variables. Let's say you can create an 
object as a 𝚌𝚘𝚗𝚜𝚝𝚒𝚗𝚒𝚝 variable and then call methods of this object to
initialize other static variables. 
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <cmath>
#include <array>
#include <memory>

// Might be invoked at both compile time and runtime
constexpr int pow2(int num) {
    return num * num;
}

// Allowed to be executed only at compile-time
consteval std::size_t strictlyCompileTimeFunction(bool cond) {
    if (cond) {
        return 2;
    } else {
        return 4;
    }
}

class MyClass {
    public:
        constexpr MyClass(int v) : m_value(v) {}
        int value() const {
            return m_value;
        }
        void value(int v) {
            m_value = v;
        }
    private:
        int m_value;
};

// Constant initialized at compile time 
// Might be used at compile time
constexpr std::size_t CompileTimeConstant = strictlyCompileTimeFunction(false);

// Non-constant variable should be initialized 
// with value known at compile time, like call of constexpr constructor
constinit MyClass NonConstant = pow2(CompileTimeConstant);

// Ordinary static 
// Initialized strictly after 'NonConstant'
static double Pow = std::pow(3.0, NonConstant.value());

int main() {

    // Use 'constexpr' variable as a template parameter
    std::array<int, CompileTimeConstant> myArr;

    // Change value for 'constinit' variable
    NonConstant = 10;

    // Invoke 'constexpr' function at runtime
    int runTimeVariable = pow2(NonConstant.value());

    return 0;
}
