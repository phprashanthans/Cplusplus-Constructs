// If you need to distinguish two or more function overloads
// but the argument types fully overlap, you can use the 
// type tagging technique

#include <iostream>
#include <string_view>

// Tags
struct IPv4_t {};
struct IPv6_t {};
// Instances of Tags
constexpr inline IPv4_t IPv4 = {};
constexpr inline IPv6_t IPv6 = {};
// Single line version
constexpr inline struct IPv7_t {} IPv7 {};

struct IPAddr {
    IPAddr(IPv4_t, std::string_view addr, int port) {
        std::cout << "IPv4 - " << addr << " , " << port << std::endl;
    }
    IPAddr(IPv6_t, std::string_view addr, int port) {
        std::cout << "IPv6 - " << addr << " , " << port << std::endl;
    }
};

int main()
{
    // Calling the tagged constructors;
    IPAddr addr1(IPv4, "127.0.0.0", 80);
    IPAddr addr2(IPv6, "::1", 80);
    return 0;
}
