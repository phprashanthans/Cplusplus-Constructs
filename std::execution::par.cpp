/*----------------------------------------------------------------------------------
std::execution::par
Allows multiple threads to process elements in parallel
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> data(1000000, 1);
    std::for_each(std::execution::par, data.begin(), data.end(),
                                    /* The lambda function doubles each element*/
                                    [](int &n) { n *= 2; });
    std::cout << "Processing complete!" << std::endl;
    return 0;
}
