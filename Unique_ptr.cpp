/**************************************************************************************
In C++ memory model, we can allocate memory in the global/static regions, which lasts for
the entire execution of the application, the stack which is fast local memory but limited
and the heap, all the free RAM on your PC.
The idea behind a smart pointer is that you can allocate the smart pointer object on the
stack, heap or global memory, and internally it will have a pointer storing the address
of a memory allocated on the heap. When the smart pointer object goes out of scope, say
because of function got ended, there has been a return or an exception, it will be
automatically destroyed. And this is where the magic happens: when it is destroyed, its
destructor is called and a delete is performed inside it. With this you only worry about 
allocating the object and not the de-allocation as the "garbage" will be automatically 
collected. 
std::unique_ptr -> Only one pointer points to a specific memory region.
***************************************************************************************/

#include <iostream>
#include <algorithm>

template <typename T>
class Unique_ptr {
    public:
        // Constructor 
        Unique_ptr(T* ptr = nullptr) {
            m_ptr = ptr;
        }
        // Copy Constructor and assignment operator deleted
        Unique_ptr(const Unique_ptr&) noexcept = delete;
        Unique_ptr& operator=(const Unique_ptr&) constexpr = delete;
        // Move constructor and assignment operator 
        Unique_ptr(Unique_ptr&& up) noexcept {
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
        void operator=(Unique_ptr&& up) noexcept {
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
