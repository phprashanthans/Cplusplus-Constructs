/*-----------------------------------------------------------------------------------
PImpl Idiom in C++

It stands for Pointer to IMPLementation. It's a programming technique
used to separate a class's implementation from its interface. The primary 
goal is to reduce build dependencies and improve compilation times.
It is also known as the "Compiler Firewall" or "Cheshire Cat" idiom
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <print>

class Person {
    public:
        Person(const char*, unsigned);
        ~Person();
        Person(Person&&);
        Person& operator=(Person&&);

        Person& getChild(std::size_t idx);
        Person& addChild(const char*, unsigned);
        void info(std::size_t indent = 0) const;
    private:
        struct PImpl;
        std::unique_ptr<PImpl> pImplPtr;
};

struct Person::PImpl {
    std::string name;
    unsigned age;
    std::vector<Person> children;
};

Person::Person(const char* name, unsigned age) :
    pImplPtr(std::make_unique<PImpl>()) {
    pImplPtr->name = name;
    pImplPtr->age = age;    
}

Person::~Person() = default;
Person::Person(Person&&) = default;
Person& Person::operator=(Person&&) = default;

Person& Person::addChild(const char* name, unsigned age) {
    pImplPtr->children.emplace_back(name, age);
    return *this;
}

Person& Person::getChild(std::size_t idx) {
    return pImplPtr->children.at(idx);
}

void Person::info(std::size_t indent) const {
    const std::string prefix(indent, ' ');

    std::cout << prefix << "|- " << pImplPtr->name << 
     "(age: " << pImplPtr->age << ")" << std::endl;

    for (std::size_t i = 0; i < pImplPtr->children.size(); ++i) {
        bool isLast {i == pImplPtr->children.size() - 1};
        std::string childPrefix {prefix + (isLast ? "   " : "|  ")};
        pImplPtr->children[i].info(indent + 3);
    }
}

int main() {
    Person kakashi("Kakashi", 90);
    kakashi.addChild("Naruto Uzumaki", 60)
           .addChild("Sakura", 40)
           .addChild("Sasuke Uchchiha", 50);

    Person& naruto {kakashi.getChild(0)};
    naruto.addChild("Boruto", 25)
          .addChild("Hinata", 20);
    
    Person& hinata {naruto.getChild(1)};
    hinata.addChild("Konahanuro", 15)
          .addChild("Kabuto", 21);

    kakashi.info();
    return 0;
}



/*----------- Output --------------------
2
----------------------------------------*/
