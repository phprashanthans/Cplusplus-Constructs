/*----------------------------------------/
       Vector Implementation in C++
/----------------------------------------*/
#include <iostream>
const int EXPAND = 2;

template <typename T>
class myVector {
    private:
        T* data;
        size_t size;
        size_t capacity;
    public:
        myVector(size_t init_capacity = EXPAND) {
            data = new T[init_capacity];
            size = 0;
            capacity = init_capacity;
        }
        ~myVector() {
            delete[] data;
        }
        T* getData() const { return data; }
        size_t getSize() const { return size; }
        size_t getCapacity() const { return capacity; }
        void push_back(T val);
        void print_vector();
};
template <typename T>
void myVector<T>::push_back(T val) {
    if (size == capacity) {
        capacity = capacity * EXPAND;
        T* new_data = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }
    data[size++] = val;
}
template <typename T>
void myVector<T>::print_vector() {
    for (size_t i = 0; i < size; i++) {
        std::cout << data[i] << ", ";
    }
    std::cout << std::endl;
}

int main() {
    myVector<double> vec;
    vec.push_back(2.3);
    vec.push_back(3.3);
    vec.push_back(4.5);
    vec.print_vector();

    size_t size_vec = vec.getSize();
    std::cout << "Vector size: " << size_vec << std::endl;
    size_t memory_used = size_vec * sizeof(double);
    std::cout << "Memory used for data: " << memory_used << " bytes" << std::endl;
    size_t capacity_vec = vec.getCapacity();
    std::cout << "Vector capacity: " << capacity_vec << std::endl;
    size_t memory_enable = capacity_vec * sizeof(double);
    std::cout << "Memory enable: " << memory_enable << " bytes" << std::endl;
    std::cout << std::endl;

    vec.push_back(5.6);
    vec.push_back(7.8);
    vec.push_back(9.3);
    vec.print_vector();

    size_vec = vec.getSize();
    std::cout << "Vector size: " << size_vec << std::endl;
    memory_used = size_vec * sizeof(double);
    std::cout << "Memory used for data: " << memory_used << " bytes" << std::endl;
    capacity_vec = vec.getCapacity();
    std::cout << "Vector capacity: " << capacity_vec << std::endl;
    memory_enable = capacity_vec * sizeof(double);
    std::cout << "Memory enable: " << memory_enable << " bytes" << std::endl;
    std::cout << std::endl;

}


/*-------------Output:----------------/
/------------------------------------*/
