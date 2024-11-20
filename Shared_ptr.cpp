/* Shared Pointer: shared_ptr
*/

#include <iostream>
class Counter {
    public:
        Counter() : m_counter(0) {}
        Counter(const Counter&) = delete;
        Counter& operator=(const Counter&) = delete;
        ~Counter() {}
        void reset() {
            m_counter = 0;
        }
        unsigned int get() {
            return m_counter;
        }
        void operator++() {
            m_counter++;
        }
        void operator++(int) {
            m_counter++;
        }
        void operator--() {
            m_counter--;
        }
        void operator--(int) {
            m_counter--;
        }
        friend std::ostream& operator<<(std::ostream& os, const Counter& counter) {
            os << "Counter Value :" << counter.m_counter << std::endl;
            return os;
        }
    private:
        unsigned int m_counter{};
};

template <typename T>
class Shared_ptr {
    public:
        // Constructor
        Shared_ptr(T* ptr = nullptr) {
            m_ptr = ptr;
            m_counter = new Counter();
            (*m_counter)++;
        }
        // Copy Constructor
        Shared_ptr(Shared_ptr<T>& sp) {
            m_ptr = sp.m_ptr;
            m_counter = sp.m_counter;
            (*m_counter)++;
        }
        // reference count getter
        unsigned int use_count() {
            return m_counter->get();
        }
        // shared pointer getter
        T* get() {
            return m_ptr;
        }
        // Overload * operator
        T& operator*() {
            return *m_ptr;
        }
        // Overload -> operator
        T* operator->() {
            return m_ptr;
        }
        // Overload = operator
        void operator=(Shared_ptr sp) {
            if (m_ptr != sp.m_ptr) {
                if (m_ptr && m_counter) {
                    (*m_counter)--;
                    if (m_counter->get() == 0) {
                        delete m_counter;
                        delete m_ptr;
                    }
                }
                m_ptr = sp.m_ptr;
                if (m_ptr) {
                    m_counter = sp.m_counter;
                    (*m_counter)++;
                }
            }
        }
        // Destructor
        ~Shared_ptr() {
            (*m_counter)--;
            if (m_counter->get() == 0) {
                delete m_counter;
                delete m_ptr;
                m_counter = nullptr;
                m_ptr = nullptr;
            }
        }

        friend std::ostream& operator<<(std::ostream& os, Shared_ptr<T>& sp) {
            os << "Address pointed: " << sp.get() << std::endl;
            os << *(sp.m_counter) << std::endl; 
            return os;
        }
    private:
        T* m_ptr;
        Counter* m_counter;
};

int main() {
    // ptr1 pointing to an integer
    Shared_ptr<int> ptr1(new int(151));
    std::cout << "--- Shared pointers ptr1 ---\n";
    *ptr1 = 100;
    std::cout << "ptr1's value now: " << *ptr1 << std::endl;
    std::cout << ptr1;
    {
        // ptr2 pointing to same integer as ptr1.
        // Shared ptr reference counter increased to 2;
        Shared_ptr<int> ptr2 = ptr1;
        std::cout << "--- Shared pointers ptr1, ptr2 ---\n";
        std::cout << ptr1;
        std::cout << ptr2;
        {
            // ptr3 pointing to same integer same as ptr1 and ptr2,
            // Shared ptr reference count increased to 3;
            Shared_ptr<int> ptr3(ptr2);
            std::cout << "--- Shared pointers ptr1, ptr2, ptr3 ---\n";
            std::cout << ptr1;
            std::cout << ptr2;
            std::cout << ptr3;
        }
        Shared_ptr<int> temp(new int(11));
        ptr2 = temp;

        // ptr3 is out of scope, so destructed
        // Reference count is decreased to 2;
        std::cout << "--- Shared pointers ptr1, ptr2 ---\n";
        std::cout << ptr1;
        std::cout << ptr2;
    }
    // ptr2 is out of scope, so destructed
    // Reference count is decreased to 1;
    std::cout << "--- Shared pointers ptr1 ---\n";
    std::cout << ptr1;

    return 0;
}

/* O/P: 
*/
