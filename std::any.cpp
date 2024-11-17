/*  Storing any object in a container without void* or Hierarchies
    If you are looking to store any type of object in a container
    without using void* or creating a new hierarchy, std::any might
    be a good choice. It can store any type, but retriveing the 
    stored value requires caution, as you need to know the type to
    use std::any_cast effectively.

    One useful application for this approach is an object storage
    class that maintains a list of singletons. This class, SingletonStorage
    offers a get method that either returns an existing object or creates 
    a new one if it doesn't exist. Internally, SingletonStorage uses a hash
    map with std::type_index as the key and std::any as the value.

*/

#include <iostream>
#include <unordered_map>
#include <any>
#include <typeindex>
#include <mutex>

class SingletonStorage {
    public:
        template <typename T>
        T& get() {
            std::lock_guard<std::mutex> lock(mutex_);  // Ensure thread safety
            std::type_index typeIndex(typeid(T));

            // Check if the object already exists
            auto it = storage.find(typeIndex);
            if (it != storage.end()) {
                // Retrieve and cast the stored object
                return std::any_cast<T&>(it->second);
            }
            // Create a new instance if not found
            T& instance = *new T();
            storage[typeIndex] = instance;
            return instance;
        }
        // Delete copy and assignment operators to ensure singleton behaviour
        SingletonStorage(const SingletonStorage&) = delete;
        SingletonStorage& operator=(const SingletonStorage&) = delete;
        
        static SingletonStorage& instance() {
            static SingletonStorage instance;
            return instance;
        }
    private:
        SingletonStorage() = default;
        std::unordered_map<std::type_index, std::any> storage;
        std::mutex mutex_;    // Mutex to ensure thread safety
};

class MyClass1 {
    public:
        void display() const {
            std::cout << "MyClass1 instance\n";
        }
};
class MyClass2 {
    public:
        void show() const {
            std::cout << "MyClass2 instance\n";
        }
};

int main() {
    // Retrieve and use instances of MyClass1 and MyClass2 from SingletonStorage
    auto& obj1 = SingletonStorage::instance().get<MyClass1>();
    auto& obj2 = SingletonStorage::instance().get<MyClass2>();

    obj1.display();
    obj2.show();

    // Retrieve the same instances again to verify singleton behaviour
    auto& sameObj1 = SingletonStorage::instance().get<MyClass1>();
    auto& sameObj2 = SingletonStorage::instance().get<MyClass2>();

    sameObj1.display();
    sameObj2.show();

    return 0;
}

/* O/P: 
MyClass1 instance
MyClass2 instance
MyClass1 instance
MyClass2 instance
*/
