/*---------------------------------------------------------------------------------
std::flat_set provides a similar interface to std::set but is implemented on top 
of a sorted container, such as std::vector or std::deque.
----------------------------------------------------------------------------------*/
#include <iostream>
#include <flat_set>    // Requires C++23
#include <string>

int main() {
    std::flat_set<int> ids = {10, 20, 30, 21, 212, 1092};

    // Attempt to insert a duplicate number/element
    auto result = ids.insert(20);
    if (!result.second) {
        std::cout << "Element with id '20' already exists in the set.\n";
    }

    // Iterate and print elements (will be in sorted order)
    std::cout << "Ids in the set: \n";
    for (const auto& id : ids) {
        std::cout << id << '\n';
    }

    // Check if an element exists
    if (ids.contains(212)) {
        std::cout << "'212' is in the set.\n";
    } else {
        std::cout << "'212' is not in the set. \n";
    }

    // Erase an element
    ids.erase(21);
    std::cout << "After erasing '21': \n";
    for (const auto& id : ids) {
        std::cout << id << '\n';
    }
    return 0;
}

/*----------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
