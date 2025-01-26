/*---------------------------------------------------------------------------------
String validation at compile time!
Since C++20, it is possible to use a struct object as a non-type template parameter,
enabling compile-time validation. In order to achieve that you need a struct as
wrapper around static string. The string can be validated at compile time to 
ensure correctness or to check whether the number of passed parameters matches the
format.
----------------------------------------------------------------------------------*/
#include <iostream>
#include <string_view>
#include <stdexcept>

// Validate string
constexpr bool is_valid(char c) {
    constexpr std::string_view valid = "0123456789 \
                                        ABCDEFGHIJKLMNOPQRSTUVWXYZ \
                                        abcdefghijklmnopqrstuvwxyz";
    return valid.find(c) != std::string_view::npos;
}

// Wrapper around the static string
template <size_t N> 
struct Format {
    constexpr Format(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }
    constexpr bool isValid() const {
        if constexpr (N == 0) {
            return false;
        }
        for (char ch : value) {
            if(ch != '\0' && !is_valid(ch)) {
                return false;
            }
        }
        return true;
    }
    constexpr std::string_view format() const {
        return value;
    }
    char value[N];
};

// Function template with a non-type template parameter
template <Format Fmt>
void processString() {
    static_assert(Fmt.isValid(), "String Format is invalid!");
    std::cout << "Processing string: " << Fmt.format() << std::endl;
}

int main() {
    processString<"Valid123">(); // Compiles successfully
    // processString<"Invalid@Char">(); // Fail at compile time
    return 0;
}
/*---------------------------------------------------------------------------------
Processing string: Valid123
----------------------------------------------------------------------------------*/
