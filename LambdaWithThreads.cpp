/*---------------------------------------------------------------------------------
Understanding threads with lambda: Pitfalls and Best Practices
----------------------------------------------------------------------------------*/
#include <iostream>
#include <thread>

std::thread createThread() {
    int value = 42;
    
    // 1) Dangling Reference: Lambda capturing value by reference
    // To fix this, capture by value not reference then lambda will have its own copy
    return std::thread([&value]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Value: " << value << std::endl; // Accessing an expired variable
    });
}

int main() {
    std::thread t = createThread();
    t.join();    // Triggers undefined behavior
    return 0;
}

/*----------------------------------------------------------------------------------
Captured by Refernce:
Value: 2
Captured by Value
Value: 42
----------------------------------------------------------------------------------*/
