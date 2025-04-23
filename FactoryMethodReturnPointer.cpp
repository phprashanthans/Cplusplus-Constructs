/*----------------------------------------------------------------------------------
A factory should return std::unique_ptr and not shared_ptr
std::unique_ptr can be converted into std::shared_ptr but not vice-versa
Using shared_ptr comes with extra overhead due to refernce counting
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <memory>

// Interface
class MyInterface {
    public:
        virtual ~MyInterface() = default;
        virtual void foo() = 0;
};

// Implementation
class myImpl : public MyInterface {
    public:
        void foo() {
            std::cout << "Foo!" << std::endl;
        }
};

// Factory Method
std::unique_ptr<MyInterface> myInterfaceFactory() {
    return std::make_unique<myImpl>();
}

int main() {
    // Construct a unique pointer
    auto uniq = myInterfaceFactory();
    uniq->foo();

    // Convert unique pointer to shared one
    auto shared = std::shared_ptr{std::move(uniq)};
    shared->foo();
    return 0;
}
