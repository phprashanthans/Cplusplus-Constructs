/* ------------------------------------------------------------------------------
An important aspect of the conditional operator is that, as an expression, 
it must have a well-defined type. If the two right-side operands do not 
align on a type, conversions may be applied to arrive at a compatible common type.
--------------------------------------------------------------------------------*/

#include <array>
#include <string>
#include <stdexcept>

// Simple Logic
int x = 1;
int y = 2;
int abs_diff = x < y ? y - x : x - y;
// abs_diff = 1

// Useful for initializing variables that do not
// support default initialization
struct MustBeInit {
    MustBeInit(int v) : v(v) {}
    int v;
};
MustBeInit m = true ? 1 : 2;
// m.v = 1

// Inject logic into const evaluated code
constexpr bool has_many = true;
std::array<int, has_many ? 1024 : 8> arr;

// When mixing types, standard conversions are permitted.
struct A {};
struct B : A {};
auto r1 = true ? 2.0 : 1; // int->double
// decltype(r1) == double
auto r2 = true ? A() : B();
// decltype(r2) == A

// Throw exceptions are permitted, as they break flow:
std::string* ptr = nullptr;
try {
    auto len = ptr ? ptr->length() : throw std::runtime_error("Null Pointer derefernce");
    // decltype(len) == size_t;
} catch(...) {}

auto r3 = []{ return true ? throw 1 : throw 2; };
// decltype(r3) = void

// When mixing cv-qualifiers, the arguments need to overlap,
// but the result is then most qualified type
int a = 1;
const int& b = 2;
int& c = a;
auto &r4 = true ? b : c;
// decltype(r4) == const int&
