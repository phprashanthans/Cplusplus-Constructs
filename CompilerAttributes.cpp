/*---------------------------------------------------------------------------------
likely: indicates to the compiler which conditional branch is more likely to occur.
This can help compiler optimize for most frequent case.
assume: specifies certain conditions or assumptions, which can be used by compiler
to generate more optimized code.
----------------------------------------------------------------------------------*/

#include <iostream>
#include <vector>

// Function to demonstarte '[[likely]]' attribute
void checkNumbers(const std::vector<int>& numbers) {
    for(const auto& num : numbers) {
        if(num > 0) [[likely]] {
            std::cout << num << " is positive." << std::endl;
        } else {
            std::cout << num << " is non-positive." << std::endl;
        }
    }
}
// Function to demonstrate '[[assume]] attribute
void process(int value) {
    // Tell the compiler we assume value > 10.
    [[assume(value > 10)]];
    std::cout << "Processing value: " << value << std::endl;

    // The compiler can optimize knowing value > 10 is always true.
    if (value > 50) {
        std::cout << "Value is significantly large." << std::endl;
    }
}

int main() {
    std::vector<int> numbers = {1, 2, 3, -1, 5};
    std::cout << "Demonstrating '[[likely]]:" << std::endl;
    checkNumbers(numbers);
    std::cout << "Demonstrating [[assume]]:" << std::endl;
    int value = 20; // Ensure value is > 10 for valid [[assume]]
    process(value);
    return 0;
}
