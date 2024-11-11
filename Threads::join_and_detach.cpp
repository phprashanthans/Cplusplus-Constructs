/* Thread synchronization:
    join() synchronizes with the thread while detach() runs the thread
    independently. join() ensures the thread waits for the completion,
    but detach() does not. Once a thread is detached, you can no longer
    interact with it. whereas a joined thread can be safely synchronized.
*/
#include <iostream>
#include <thread>
#include <chrono>

void fun() {
    for(int i=0; i<5; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1'000));
        std::cout << "in fun. count:" << i + 1 << std::endl;
    }
}
void fun2() {
    for(int i=0; i<5; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "in fun2. count:" << i + 1 << std::endl;
    }
}

int main() {
    std::thread t1(&fun);
    std::thread t2(&fun2);
    t1.detach();
    t2.join();
    return 0;
}

/* O/P: 
    in fun2. count:1
    in fun. count:1
    in fun2. count:2
    in fun2. count:3
    in fun. count:2
    in fun2. count:4
    in fun2. count:5
*/
