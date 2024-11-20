#include <iostream>

template <typename T>
class Unique_ptr {
    public:
        // Constructor 
        Unique_ptr(T* ptr = nullptr) {
            m_ptr = ptr;
        }
        // Copy Constructor and assignment operator deleted
        Unique_ptr(const Unique_ptr&) = delete;
        Unique_ptr& operator=(const Unique_ptr&) = delete;
        // Move constructor and assignment operator 
        Unique_ptr(Unique_ptr&& up) {
            m_ptr = up.m_ptr;
            up.m_ptr = nullptr;
        }
        // unique pointer getter
        T* get() const noexcept {
            return m_ptr;
        }
        // Overload * operator
        T& operator*() const noexcept {
            return *m_ptr;
        }
        // Overload -> operator 
        T* operator->() const noexcept {
            return m_ptr;
        }
        // Overload = operator
        void operator=(Unique_ptr&& up) {
            if (m_ptr != up.m_ptr) {
                delete m_ptr;
                m_ptr = up.m_ptr;
                up.m_ptr = nullptr;
            }
        }
        // Destructor
        ~Unique_ptr() {
            delete m_ptr;
            m_ptr = nullptr;
        }
    
        friend std::ostream& operator<<(std::ostream& os, Unique_ptr<T>& up) {
            os << "Address Pointed: " << up.get() << std::endl;
            return os;
        }
    private:
        T* m_ptr;
};

int main() {
    Unique_ptr<int> ptr1(new int(10));
    std::cout << "Value at Ptr1: " << *ptr1 << std::endl;
    std::cout << ptr1;

    Unique_ptr<int> ptr2 = std::move(ptr1);
    std::cout << "Value at Ptr2: " << *ptr2 << std::endl;
    std::cout << ptr2;
}
