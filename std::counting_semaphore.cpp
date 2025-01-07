/*---------------------------------------------------------------------------------
Synchronization Primitives 
std::counting_semaphore : A counter that can be decreased using the acquire method, 
and if it reaches 0, the thread that called acquire is blocked. By invoking release,
the internal counter is incremented, and if there are any blocked threads, they are
unblocked. 
Use case: Let's say you have a limited number of resources and more threas that 
need to use them. The counting semaphore can be useful here, allowing only a limted
number of threads to be active at any given moment.
----------------------------------------------------------------------------------*/
#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <chrono>

constexpr int RESOURCE_COUNT = 5;  // Number of available resources
std::counting_semaphore<RESOURCE_COUNT> semaphore(RESOURCE_COUNT);

void accessResource(int threadId) {
    semaphore.acquire();
    std::cout << "Thread " << threadId << " acquired a resource.\n";

    // Simulate work with resource
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Thread " << threadId << " released a resource.\n";
    semaphore.release();
}

int main() {
    std::vector<std::thread> threads;

    // Create multiple threads that require access to the resources
    for(int i=0; i<10; i++) {
        threads.emplace_back(accessResource, i);
    }
    for(auto& t : threads) {
        t.join();
    }

    return 0;
}
