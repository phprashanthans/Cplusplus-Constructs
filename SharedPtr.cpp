/*
Using std::shared_ptr in C++ allows you to manage the lifetime of objects
dynamically and share ownership among multiple parts of your code.
Instead of defining a global variable, you can use shared_ptr to 
ensure that the memory is cleaned up automatically when it;s no
longer needed. 
*/
#include<iostream>
using namespace std;

class Service {
public:
    void hello() {
        std::cout << "Hello World!\n";
    }
    static inline std::shared_ptr<Service> create() {
        return std::make_shared<Service>();
    }
};
class Application {
public:
    Application(std::shared_ptr<Service> service) : service_(service) {
    }
    int exec() {
        service_->hello();
        return 0;
    }
private:
    std::shared_ptr<Service> service_;
};

int main() {
    Application(Service::create()).exec();
    return 0;
}
