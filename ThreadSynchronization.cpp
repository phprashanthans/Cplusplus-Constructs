/*----------------------------------------------------------------------------------
Thread Synchronization
1) Mutex or Locks
2) Condition Variables
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// Using Mutex

std::mutex mtx;
int counter = 0;

void increment() {
    std::lock_guard<std::mutex> lock(mtx);
    ++counter;
}

void printMessage() {
    std::cout << "Hello from the new thread!" << std::endl;
}

int main() {
    std::thread t(printMessage);
    std::thread t1(increment);
    std::thread t2(increment);

    t.join();
    t1.join();
    t2.join();
    std::cout << "Counter: " << counter << std::endl;
    return 0;
}

// Using Condition Variable

std::condition_variable cv;
int data = 0;

void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate work
    {
        std::lock_guard<std::mutex> lock(mtx);
        data = 42;  // Produce data
    }
    cv.notify_one();  // Notify consumer thread
}
void consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [](){ return data != 0; });  // Wait until data is produced
    std::cout << "Consumed data: " << data << std::endl;
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
