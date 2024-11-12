/* 
    Function Try Catch Block Syntax
*/

#include <iostream>

class Error {
    public:
        Error() noexcept(false) {
            throw std::runtime_error("Constructor");
        }
        ~Error() noexcept(false) {
            throw std::runtime_error("Destructor");
        }
        void error() noexcept(false) {
            throw std::runtime_error("Method");
        }
};
class Foo {
    public:
        Foo() try {
        } catch (const std::exception& ex) {
            std::cout << "Constructor exception: " << ex.what() << std::endl;
        }
        ~Foo() try {
        } catch (const std::exception& ex) {
            std::cout << "Destructor exception: " << ex.what() << std::endl;
            return;
        }
        void foo() try {
            m_error.error();
        } catch (const std::exception& ex) {
            std::cout << "Method foo exception: " << ex.what() << std::endl;
        }
    private:
        Error m_error;
};

int main() {
    try {
        Foo foo;
        foo.foo();
    } catch(const std::exception& ex) {
        std::cout << "exception: " << ex.what() << std::endl;
    }
    return 0;
}

/* O/P: 
    Constructor exception: Constructor
    exception: Constructor
*/
