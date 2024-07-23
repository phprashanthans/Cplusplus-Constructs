#include <iostream>
#include <bit>

int main()
{
    if constexpr (std::endian::native == std::endian::little) {
        std::cout << "This system is little-endian" << std::endl;
    } else if constexpr (std::endian::native == std::endian::big) {
        std::cout << "This system is big-endian" << std::endl;
    } else {
        std::cout << "This system is mixed-endian" << std::endl;
    }
    return 0;
}
