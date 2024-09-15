#include <iostream>
#include <vector>
#include <numeric>
#include <ranges>

int main()
{
    std::vector<std::string> animals {
        "Elephant", "Tiger", "Kangaroo", "Penguin", "Dolphin"
    };
    std::vector<int> indices(animals.size());
    // Fills indices with consecutive numbers starting from 0 (third argument)
    std::iota(indices.begin(), indices.end(), 0);
    for(const auto& index : indices) {
        // std::cout << index << ": " << animals[index] << std::endl;
    }
    // Assumes element Contiguity like std::vector
    for(auto&& name : animals) {
        auto const index = std::distance(&animals[0], &name);
        // std::cout << index << ": " << name << "\n";
    }
    // For-loop init statement requires C++20
    for(std::size_t index = 0; const auto& name : animals) {
        //std::cout << index << ": " << name << "\n";
        ++index;
    }
    // Ranges require C++23
    for(auto&& [index, name] : std::views::enumerate(animals)) {
        //std::cout << index << ": " << name << "\n";
    }
    
    for(auto&& [index, name] : std::views::zip(std::views::iota(0u, animals.size()), animals)) {
        std::cout << index << ": " << name << "\n";
    }
    return 0;
}
