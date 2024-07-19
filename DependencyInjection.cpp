#include <iostream>
#include <memory>
using namespace std;

struct Service {
    virtual void make_important_call() = 0;  
};
struct FakeService : Service {
    void make_important_call() override {
        std::cout << "Operated by FakeService" << std::endl;
    }
};
struct ProductionService : Service {
    void make_important_call() override {
        std::cout << "Operated by ProductionService" << std::endl;
    }
};
struct MyClass {
    private:
        std::unique_ptr<Service> dependency_;
    public:
        MyClass(std::unique_ptr<Service> service) :
            dependency_(std::move(service)) {}
        void operate() {
            dependency_->make_important_call();
        }
};

int main() {
    MyClass m(std::make_unique<ProductionService>());
    m.operate();
    MyClass n(std::make_unique<FakeService>());
    n.operate();
}
