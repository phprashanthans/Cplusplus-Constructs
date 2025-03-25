/*----------------------------------------------------------------------------------
Exception Handling
-----------------------------------------------------------------------------------*/
#include <iostream>

void checkAge(int age) {
    if (age < 10) {
        throw std::invalid_argument("Age must be 18 or older");
    }
    std::cout << "Age is valid: " << age << std::endl;
}
void callerFunction() {
    checkAge(15);  // Throws an exception
}

int main() {
    // Catching an Exception
    try {
        checkAge(16);  // Throws an exception
    } catch (const std::invalid_argument& e) {
        std::cerr << "Caught Exception: " << e.what() << std::endl;
    }

    // Propagating Exceptions
    try {
        callerFunction();
    } catch (const std::invalid_argument& e) {
        std::cerr << "Handled in main: " << e.what() << std::endl;
    }

    // Re-throwing an exception
    try {
        try {
            checkAge(14);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Logging exception: " << e.what() << std::endl;
            throw;  // Re-throw the same exception
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Handled at a higher level: " << e.what() << std::endl;
    }
    return 0;
}

// Custom Exceptions
class CustomException : public std::exception {
    private:
        std::string message;
    public:
        explicit CustomException(const std::string& msg) : message(msg) {}
        const char* what() const noexcept override {
            return message.c_str();
        }
};
void performTask(bool fail) {
    if (fail) {
        throw CustomException("Custom error: Task failed!");
    }
}
