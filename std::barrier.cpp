/*---------------------------------------------------------------------------------
std::barrier is a synchronization primitive that blocks threads in group until all 
the threads have reached the barrier. 
Let's say you have a group of threads with a job spilt accross them. Once they finish
their assigned tasks, the fastest threads should wait for all others to catch up 
before the job can be split again. std::barrier has a countdown, and an optional 
callback can be executed once the counter reaches 0. Each thread can decrement the 
counter using the wait call.
----------------------------------------------------------------------------------*/
#include <iostream>
#include <thread>
#include <vector>
#include <barrier>
#include <atomic>

int main() {
    // A shared resource for the barrier's callback to update
    std::atomic<int> intermediate_result{0};
    const int thread_count = 2;
    
    // Barrier's callback to calculate intermediate result
    auto barrier_callback = [&intermediate_result]() {
        std::cout << "Barrier callback: Intermediate result calculated: " << 
            intermediate_result.load() << "\n";
    };
    // Create a barrier for synchronization with a callback
    std::barrier sync_point(thread_count, barrier_callback);

    auto worker = [&sync_point, &intermediate_result](int id) {
        // Stage1: Initial Work
        int local_result = id * 10;  // Simulated work
        std::cout << "Thread " << id << " completed stage 1 with result: " << local_result << "\n";

        // Store local result into shared intermediate result
        intermediate_result.fetch_add(local_result);

        // Synchronize at the barrier
        sync_point.arrive_and_wait();

        // Stage2: Continue work after synchronization
        std::cout << "Thread " << id << " resuming work after barrier with intermediate result: " 
            << intermediate_result.load() << std::endl;
        int final_result = local_result + intermediate_result.load();  // Simulated further work
        std::cout << "Thread " << id << " completed stage 2 with final result: " << final_result << "\n";
    };

    // Start worker threads
    std::vector<std::thread> threads;
    for(int i=0; i<thread_count; i++) {
        threads.emplace_back(worker, i+1);
    }

    // Join all threads
    for(auto& t : threads) {
        t.join();
    }

    std::cout << "All threads have finished. Final intermediate result: " << intermediate_result.load() << "\n";
    return 0;
}
