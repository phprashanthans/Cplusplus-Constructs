/* A pointer to a method in C++ differs from an ordinary pointer to a 
   function in one small detail - it requires a pointer to its object 
   as the first parameter. Using std::bind, you can convert it to a 
   'normal' callable object
*/
#include <iostream>
#include <functional>

class MyClass {
    public:
        void displayMessage(const std::string& message) {
            std::cout << "Message: " << message << std::endl;
        }
        int add(int a, int b) {
            return a+b;
        }
};

int main() {
    MyClass obj;
    // Pointer to member function 'displayMessage' of MyClass
    void (MyClass::*displayPtr)(const std::string&) = &MyClass::displayMessage;
    // Calling member function using pointer-to-member
    (obj.*displayPtr)("Hello, using pointer to member function!");
    // Using std::bind to bind 'this' (obj) to the member function
    auto boundDisplay = std::bind(displayPtr, &obj, std::placeholders::_1);
    // Call the bound function with just the remaining argument
    boundDisplay("Hello, using std::bind");

    // Another example: Binding 'add' method with 'std::bind'
    int (MyClass::*addPtr)(int, int) = &MyClass::add;
    auto boundAdd = std::bind(addPtr, &obj, std::placeholders::_1, std::placeholders::_2);
    int result = boundAdd(5, 10);
    std::cout << "Result of addition: " << result << std::endl;
    return 0;
}

/* O/P: 
  Message: Hello, using pointer to member function!
  Message: Hello, using std::bind
  Result of addition: 15  
*/
