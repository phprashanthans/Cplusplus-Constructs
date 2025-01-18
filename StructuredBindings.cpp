/*---------------------------------------------------------------------------------
Structured Bindings, Since C++17
Unpack multiple values into separate variables in a single step.
Can be used for tuples and pairs, structs and classes, range based loops
----------------------------------------------------------------------------------*/
#include <iostream>
#include <tuple>
#include <map>

int main() {
    // Without Structured Bindings
    std::tuple<int, double, std::string> data1 = {42, 3.14, "C++"};
    int x = std::get<0>(data1); 
    double y = std::get<1>(data1);
    std::string z = std::get<2>(data1);
    std::cout << x << ", " << y << ", " << z << std::endl;

    // With Structured Bindings
    std::tuple<int, double, std::string> data2 = {42, 3.14, "C++"};
    auto [p, q, r] = data2;
    std::cout << p << ", " << q << ", " << r << std::endl;

    // Combining with std::map
    std::map<int, std::string> data3 = {{1, "one"}, {2, "two"}};
    for (const auto& [key, value] : data3) {
        std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }
    return 0;
}
/*----------------------------------------------------------------------------------
42, 3.14, C++
42, 3.14, C++
Key: 1, Value: one
Key: 2, Value: two
----------------------------------------------------------------------------------*/
