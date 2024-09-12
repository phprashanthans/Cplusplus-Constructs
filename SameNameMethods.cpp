// C++ allows the definition of functions or methods with the same name
// where the compiler decided which one to execute

#include <iostream>
#include <string>

// different parameter types
void foo(int);
void foo(std::string);
void foo(int, std::string);

// different parameters qualifiers
void foo(std::string *);
void foo(const std::string *);
void foo(const std::string &);
void foo(std::string &&);
void foo(std::string &);

// template resolution
class Base {};
template <typename T>
void foo(const T&);
template<>
void foo<int>(const int&);

// class qualifiers
class Foo {
    public:
        void bar() const &;
        void bar() &;
        void bar() volatile &;
        void bar() &&;
        void bar() const &&;
        void bar() volatile &&;
};
