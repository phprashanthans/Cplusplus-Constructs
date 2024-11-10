#include <iostream>
#include <vector>
#include <random>

// vector generator
std::vector<int> make_vector(std::size_t size) {
    std::vector<int> vec(size);
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};
    std::uniform_int_distribution<int> dist {1, 52};
    std::generate(vec.begin(), vec.end(), [&mersenne_engine, &dist]{ return dist(mersenne_engine);});
    return vec;
}
int main() {
    std::vector<int> res = make_vector(10);
    for(auto el : res) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}
