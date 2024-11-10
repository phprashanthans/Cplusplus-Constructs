/* In some cases, it may be necessary to transfer a value from one thread to another.
If this is a one-time action, a pair consisting of 'std::promise' and 'std::future'
is a good candidate for the task. std::promise is used to set the value while
std::future is used to obtain that value in a blocking manner. 
*/
#include <iostream>
#include <thread>
#include <future>

int main() {
    auto promise = std::promise<std::string>{};
    auto th = std::jthread([&promise](){
        promise.set_value("from thread");
    });
    auto future = promise.get_future();

    // obtain the value in a blocking way
    auto str = future.get();
    std::cout << str << std::endl;
}
