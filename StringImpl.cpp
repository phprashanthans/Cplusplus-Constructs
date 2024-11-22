#include <iostream>
#include <string>

class String {
    private:
        char* m_buffer = nullptr;
        unsigned int m_size = 0;
    public:
        // default constructor
        String() : m_buffer(nullptr), m_size(0) {}
        // Parametrized constructor
        String(const char* const buffer) {
            std::cout << "Parametrized Constructor\n";
            m_size = strlen(buffer);
            m_buffer = new char[m_size + 1]; // +1 for keeping the null character
            strncpy(m_buffer, buffer, m_size);
        }
        // Copy Constructor
        String(const String& str) {
            std::cout << "Copy Constructor\n";
            m_size = str.m_size;
            m_buffer = new char[m_size + 1];
            strncpy(m_buffer, str.m_buffer, m_size);
        }
        // Copy Assignment
        String& operator=(const String& str) {
            std::cout << "Copy Assignment\n";
            cleanup();
            m_size = str.m_size;
            m_buffer = new char[m_size + 1];
            strncpy(m_buffer, str.m_buffer, m_size);
            return *this;
        }
        // Move Constructor
        String(String&& str) {
            std::cout << "Move Constructor\n";
            cleanup();
            m_size = str.m_size;
            m_buffer = str.m_buffer;
            str.m_buffer = nullptr;
            str.m_size = 0;
        }
        // Move Assignment
        String& operator=(String&& str) {
            std::cout << "Move Assignment\n";
            cleanup();
            m_size = str.m_size;
            m_buffer = str.m_buffer;
            str.m_buffer = nullptr;
            str.m_size = 0;
            return *this;
        }
        // Operator '+' Overloading
        String operator+(const String& str) {
            String s;
            s.m_size = this->m_size + str.m_size;
            s.m_buffer = new char[s.m_size + 1];
            strncpy(s.m_buffer, this->m_buffer, this->m_size);
            strncpy(s.m_buffer + this->m_size, str.m_buffer, str.m_size);
            return s;
        }
        // Get Length
        unsigned int length() const {
            return m_size;
        }
        // Get character buffer
        const char* c_str() const {
            return m_buffer;
        }
        ~String() {
            cleanup();
        }
    private:
        void cleanup() {
            if (m_buffer != nullptr) {
                delete[] m_buffer;
            }
            m_size = 0;
        }
        friend std::ostream& operator<<(std::ostream& os, const String& str) {
            std::cout << str.c_str() << std::endl;
            return os;
        }
};

int main() {
    String a("Naruto_Uzumaki");
    String b(a);
    String c(std::move(a));
    c = b;
    c = std::move(b);
    return 0;
}

/*----Output:--------------------------
Parametrized Constructor
Copy Constructor
Move Constructor
Copy Assignment
Move Assignment
-------------------------------------*/
