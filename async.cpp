/* std::async can be useful in different scenarios: it can either execute an 
operation in a dedicated thread or defer the launch of operation until it is
actually needed.
Syntax:
    auto ans = std::async(std::launch::async, func_name, arg_list...)
*/
#include <iostream>
#include <vector>
#include <random>
#include <future>

// vector generator
std::vector<int> make_vector(std::size_t size) {
    std::vector<int> vec(size);
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};
    std::uniform_int_distribution<int> dist {1, 52};
    std::generate(vec.begin(), vec.end(), [&mersenne_engine, &dist]{ return dist(mersenne_engine);});
    return vec;
}
// some heavy function
int sum(std::vector<int> number) {
    return std::accumulate(number.begin(), number.end(), 0);
}
int main() {
    // example with execution in a separated thread
    {
        auto numbers = make_vector(100'000);
        // launch operation in the separated thread
        auto total = std::async(std::launch::async, sum, std::move(numbers));
        // block until operation will be finished
        std::cout << total.get() << std::endl;
    }
    // example with deferred execution
    {
        auto numbers = make_vector(100'000);
        // defer execution of heavy function till the moment when result is needed
        auto total = std::async(std::launch::deferred, sum, std::move(numbers));
        // execute function in current thread and obtain the result
        std::cout << total.get() << std::endl;
    }
}
