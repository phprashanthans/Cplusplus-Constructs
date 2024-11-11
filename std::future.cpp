/* std::async => If there is a need to run a function asynchronously without
much complexity, this is an option. It manages thread creation and returns a 
std::future automatically, which can be used to get the result when task is done.
std::async can decide whether to run the function on a separate thread or defer
execution (depending on launch policy).
*/

#include <iostream>
#include <array>
#include <numeric> // For std::accumulate
#include <random>  // For Random number generation
#include <chrono>  // For seeding randomness
#include <future>

long computeSum(const std::array<int, 1000000>& data, size_t start, size_t end) {
    return std::accumulate(data.begin() + start, data.begin() + end, 0);
}

void fillWithRandomNumbers(std::array<int, 1000000>& data) {
    std::mt19937 rng(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, 100);
    for (auto& num : data) {
        num = dist(rng);
    }
}

int main() {
    std::array<int, 1000000> data;
    fillWithRandomNumbers(data);
    size_t partSize = data.size() / 4;

    std::future<long> sum1 = std::async(std::launch::async, computeSum, std::cref(data), 0, partSize);
    std::future<long> sum2 = std::async(std::launch::async, computeSum, std::cref(data), partSize, 2 * partSize);
    std::future<long> sum3 = std::async(std::launch::async, computeSum, std::cref(data), 2 * partSize, 3 * partSize);
    std::future<long> sum4 = std::async(std::launch::async, computeSum, std::cref(data), 3 * partSize, data.size());

    long sum = sum1.get() + sum2.get() + sum3.get() + sum4.get();
    std::cout << "Total Sum: " << sum << std::endl;
    return 0;
}

/* O/P: 
*/
