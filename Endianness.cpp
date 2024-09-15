#include <iostream>
#include <bit>
// Since C++20
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

// Before C++20
int main() {
    unsigned int num = 0x123456;
    char* ptr = (char*)&num;
    if(*ptr == 0x67) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }
    return 0;
}
