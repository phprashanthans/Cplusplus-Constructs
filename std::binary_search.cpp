/*---------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <algorithm>

// Function to check if an element exists in the sorted vector
bool contains(const std::vector<int>& vec, int value) {
    return std::binary_search(vec.begin(), vec.end(), value);
}

int main() {
    std::vector<int> sortedVec;

    //Insert elements
    sortedVec.push_back(10);
    sortedVec.push_back(5);
    sortedVec.push_back(20);
    sortedVec.push_back(15);
    // Sorting after insertion
    std::sort(sortedVec.begin(), sortedVec.end());

    // Print sorted vector
    for(int num : sortedVec) {
        std::cout << num << " ";
    }
    std::cout << "\n";

    // Check for element existence
    int searchElement = 15;
    if (contains(sortedVec, searchElement)) {
        std::cout << searchElement << " is in the vector.\n";
    } else {
        std::cout << searchElement << " is not in the vector.\n";
    }
    return 0;
}

/*----------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
