/*----------------------------------------------------------------------------------
Coroutines are one of the powerful features introduced with the C++20 standard.
Coroutines are functions that can pause their execution (suspend) and later resume it.
Useful in asynchronous programmiing such as handling long-running taks (e.g. I/O operations
or network communications) without blocking the main thread. 
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <coroutine>
#include <chrono>
#include <thread>

struct simple_awaiter {
    std::chrono::milliseconds delay;
    bool await_ready() const noexcept {
        return delay.count() <= 0; 
    }
    void await_suspend(std::coroutine_handle<> handle) const {
        std::thread([handle, this] {
            std::this_thread::sleep_for(delay);
            handle.resume();
        }).detach();
    }
    void await_resume() const noexcept {
        // No operation, continue execution after resuming
    }
};

struct MyCoroutine {
    struct promise_type {
        MyCoroutine get_return_object() {
            return {std::coroutine_handle<promise_type>::from_promise(*this)}; 
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> handle_;
};

// Corotine function
MyCoroutine async_wait(std::chrono::milliseconds delay) {
    std::cout << "Coroutine is about to be suspended...\n";
    co_await simple_awaiter{delay};
    std::cout << "Coroutine has been resumed\n";
    co_return;  // End the coroutine
}

int main() {
    std::cout << "Main start" << std::endl;
    auto coro = async_wait(std::chrono::seconds(2));
    std::cout << "Main continue while coroutine is suspended\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
/*-----------------------------------------------------------------------------------
------------------------------------------------------------------------------------*/
