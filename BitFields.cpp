/*-----------------------------------------------------------------------------------
Bitfields are defined in C++. It is a way to tell the compiler exactly how many bits 
to allocate for each data member. Normally, the smallest addressable unit in C++ is 
a char (1 byte / 8 bits). But what if your data only needs a bit or two? 
That’s where bitfields come in.
Instead of storing flags and metadata in separate full-sized members, you can  
compactly pack them together, leading to more efficient memory layouts.
While there are other alternatives such as `std::bitset` and `std::vector<bool>`,
they still require manual indexing and parsing for each logical field. Bitfields let 
you declare meaningful, named fields and access them just like any other struct member.
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <bitset>

// Size: 3 bool(3B) + Padding (1B) + uint16_t(2B)
struct FileMeta {
    bool          compressed {1};
    bool          encrypted  {0};
    bool          hidden     {0};
    std::uint16_t filesize   {1234};
};

// Size: 15 bits, packed in 2 bytes
struct FileMetaBF {
    std::uint16_t
        compressed :  1 {1},    // LSB
        encrypted  :  1 {0},
        hidden     :  1 {0},
        filesize   : 12 {1234}; // MSB
};

int main() {
    FileMeta meta;
    FileMetaBF metaBF;
    auto bits {std::bitset<16>{std::bit_cast<std::uint16_t>(metaBF)}};
    std::cout << std::format(
        "--- File Metadata Layout Comparison ---\n"
        "Traditional struct size   : {:>2} bytes\n"
        "Bitfield struct size      : {:>2} bytes\n"
        "\nBitfield raw layout (MSB->LSB):\n{}\n",
        sizeof(meta), sizeof(metaBF), bits.to_string()
    );
    return 0;
}

/*----------- Output --------------------
--- File Metadata Layout Comparison ---
Traditional struct size   :  6 bytes
Bitfield struct size      :  2 bytes

Bitfield raw layout (MSB->LSB):
0010011010010001
----------------------------------------*/
