/* The main purpose of decorator pattern is straightforward: to add new functionality to
functions without modifying existing classes.
Let's say you have an existing class hierarchy, and there is a requirement to add
concurrent protection. In this case, a decorator class is created that holds a 
pointer to the base class for call redirection. Each time a method in the 
decorator is called, the internal mutex is locked for multithreading protection,
and only then is the method from the wrapper object invoked. 
*/
#include <iostream>
#include <vector>
#include <thread>
#include <syncstream>

// Abstract Interface to inherit
class AnimalWithName {
    public:
        virtual ~AnimalWithName() = default;
    public:
        virtual void setName(const std::string& name) = 0;
        virtual std::string getName() const = 0;
};
// Implementation without protection against concurrency
class DogWithName : public AnimalWithName {
    public:
        void setName(const std::string& name) override {
            m_name = name;
        }
        std::string getName() const override {
            return "Dog_" + m_name;
        }
    private:
        std::string m_name;
};
// Adding protection against concurrent access
class MultiThreadedAnimalProxy : public AnimalWithName {
    public:
        MultiThreadedAnimalProxy(std::unique_ptr<AnimalWithName> animal) : m_animal(std::move(animal)) 
        {}
    public:
        void setName(const std::string& name) override {
            auto lock = std::lock_guard {m_mutex};
            m_animal->setName(name);
        }
        std::string getName() const override {
            auto lock = std::lock_guard {m_mutex};
            return m_animal->getName();
        }
    private:
        std::unique_ptr<AnimalWithName> m_animal;
        mutable std::mutex m_mutex;
};

int main() {
    MultiThreadedAnimalProxy animal(std::make_unique<DogWithName>());
    auto th = std::thread([&animal](){
        auto name = animal.getName();
        //std::osyncstream syncStream(std::cout);
        std::cout << "The name: " << name << std::endl;
    });
    animal.setName("Harry");
    th.join();
}
