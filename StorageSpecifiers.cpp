/*----------------------------------------------------------------------------------
Storage Specifiers:
static - shared across multiple threads. Requires synchronization for safe concurrent
processes.
thread_safe - Each thread gets its own separate instance. No synchronization needed.
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <syncstream>

static std::string GlobalSharedVariable = "Test";
thread_local std::string GlobalThreadSpecific = "Test 2";

int count() {
    // Preserve state between function calls
    static std::atomic<int> counter = 0;
    return counter++;
}
int countThreaded() {
    // Variable dedicated for each thread
    // States is preserved across function calls
    thread_local int counter = 0;
    return counter++;
}

int main() {
    std::cout << "Global Counter" << std::endl;
    // First Initialization
    std::cout << count() << std::endl;
    // Counter is incremented
    std::cout << count() << std::endl;

    std::cout << "Thread specific counter for main" << std::endl;
    // Thread specific counter
    std::cout << countThreaded() << std::endl;
    std::cout << countThreaded() << std::endl;

    auto th = std::thread([](){
        std::osyncstream synced_out(std::cout);
        synced_out << "Thread specific counter child thread" << std::endl;
        // Thread specific counter
        synced_out << countThreaded() << std::endl;
        synced_out << countThreaded() << std::endl;

        synced_out << "Global counter from child thread" << std::endl;
        // Call to the local static variable continue increasing the counter
        synced_out << count() << std::endl;
        synced_out << count() << std::endl;
    });
    th.join();
    return 0;
}
