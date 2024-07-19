#include <iostream>
#include <string_view>
using namespace std;
using namespace std::literals;

// Raw literals

// R prefix followed by "( closed by )"
string_view a = R"(C:\some\file\path)";
// Any identifier can be included
string_view b = R"some_data(R"(this is a raw string)")some_data";
// Multi line tabs/spaces are considered
string_view c = R"(When 
                using multi-line raw strings
                any leading space and newline characters
                will be part of the string)";
// can add suffix too
string_view d = R"(\"\")"sv;
int main()
{
    std::cout << a << endl;
    std::cout << b << endl;
    std::cout << c << endl;
    std::cout << d << endl;
}
