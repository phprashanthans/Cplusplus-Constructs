/*---------------------------------------------------------------------------------
std::find_if : To find elements that meet specific conditions or custom predicates
----------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <algorithm>   // std::find_if

int find_first_negative(const std::vector<int>& vec) {
    // Searches the vector vec for the first element that satisfies the lambda
    // function. If no match is found, it equals vec::end()
    auto it = std::find_if(vec.begin(), vec.end(), [](int value) {
        // Lambda function that takes an integer value, returns true if 
        // the value is negative, otherwise false
        return value < 0;
    });
    // If it iterator is valid, std::distance calculates the index of the element
    return (it != vec.end()) ? std::distance(vec.begin(), it) : -1;
}

int main() {
    std::vector<int> numbers = {1, 2, 3, -4, 5};
    int index = find_first_negative(numbers);
    if (index != -1)
        std::cout << "First negative at index: " << index << "\n";
    else 
        std::cout << "No negative found.\n";
    return 0;
}
/*---------------------------------------------------------------------------------
First negative at index: 3
----------------------------------------------------------------------------------*/
