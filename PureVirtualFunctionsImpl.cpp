#include <iostream>

class VirtualInterface {
    public:
        virtual void foo() const = 0;
        virtual ~VirtualInterface() {
            std::cout << "Destroying object for VirtualInterface\n";
        }
};
// A base class can also have the default implementation of a 
// pure virtual function. To be precise =0 means derived classes
// must provide an implementation, but base still can have it's 
// own implementation
void VirtualInterface::foo() const {
    std::cout << "Foo implementation in VirtualInterface\n";
}
class VirtualDemo1 : public VirtualInterface {
    public:
        VirtualDemo1() {
            std::cout << "Creating object for VirtualDemo1\n";
        }
        ~VirtualDemo1() {
            std::cout << "Destroying object for VirtualDemo1\n";
        }
        void foo() const override {
            std::cout << "Foo implementation in VirtualDemo1" << std::endl;
        }
};
class VirtualDemo2 : public VirtualInterface {
    public:
        VirtualDemo2() {
            std::cout << "Creating object for VirtualDemo2\n";
        }
        ~VirtualDemo2() {
            std::cout << "Destroying object for VirtualDemo2\n";
        }
        void foo() const override {
            VirtualInterface::foo();
        }
};

int main()
{
    VirtualDemo1 demo1;
    demo1.foo();
    VirtualDemo2 demo2;
    demo2.foo();
    return 0;
}
