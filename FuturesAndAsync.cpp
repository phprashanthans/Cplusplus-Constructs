/*----------------------------------------------------------------------------------
std::async is a function template that allows developers to execute a function 
asynchronously. It runs the function in a separate thread and immediately returns
a std::future object. The std::async has two primary launch policies: 
    - std::launch::async - Forces the function to execute async in new thread
    - std::launch::deferred - Delays the execution until the result is needed (when get() or wait() is called)
std::future  provides an easy mechanism for retrieving results, handling exceptions, and 
ensuring tasks are executed in parallel when necessary
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <future>
#include <chrono>

int compute_square(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate Heavy Computation
    return x * x;
}
void long_running_task() {
    std::cout << "Task is running asynchronously" << std::endl;
}

int main() {
    // Launch async task
    std::future<int> async_result = std::async(std::launch::async, compute_square, 10);

    // Perform other operations while the task is running
    std::cout << "Doing other work..." << std::endl;

    // Get the result, blocks until the task completes
    int square = async_result.get();
    std::cout << "The square of 10 is: " << square << std::endl;

    std::future<void> deferred_result = std::async(std::launch::deferred, long_running_task);
    deferred_result.get();  // This will start the task when get() is called.
    return 0;
}

// Handling Exceptions with Futures

int risky_task() {
    throw std::runtime_error("An error occured during computation!");
}

int main() {
    try {
        // Start risky asynchronous task
        std::future<int> result = std::async(std::launch::async, risky_task);
        result.get();  // This will throw exception
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}

// Using Async for Background Operations

#include <iostream>
#include <vector>
#include <future>

int process_data(int id) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return id * id;
}

int main() {
    std::vector<int> ids = {1, 2, 3, 4, 5};
    std::vector<std::future<int>> futures;

    // Launch each task asynchronously
    for (int id : ids) {
        futures.push_back(std::async(std::launch::async, process_data, id));
    }

    // Collect results
    for (auto& fut : futures) {
        std::cout << "Processed result: " << fut.get() << std::endl;
    }
    return 0;
}
