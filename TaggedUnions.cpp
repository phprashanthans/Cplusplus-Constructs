/* std::variant => Type-safe alternative for tagged unions, offering a way to
   represent a variable that can hold multiple types in the same memory space.
   std::visit => Eliminates the need for manual type checks by allowing you to
   apply a function directly to the active type. This ensures all the possible 
   types are handled safely at compile time, reducing the risk of runtime errors
   The  size of std::variant is determined by the size of largest type it can
   hold, plus some additinal space for storing type information.
*/

// Implementing a tagged union in C to define a type capable of storing
// multiple data types
#include <stdint.h>
#include <stdio.h>

typedef struct { uint8_t num; } foo_t;
typedef struct { uint16_t num; } bar_t;
typedef struct { uint32_t num; } baz_t;

typedef enum { TAG_FOO, TAG_BAR, TAG_BAZ} tag_e;
typedef struct {
    tag_e tag;
    union {
        foo_t foo;
        bar_t bar;
        baz_t baz;
    }; 
} tagged_union_t;

void tagged_union_print(tagged_union_t* self) {
    switch (self->tag) {
        case TAG_FOO: printf("Foo %i\n", self->foo.num); break;
        case TAG_BAR: printf("Bar %i\n", self->bar.num); break;
        case TAG_BAZ: printf("Baz %i\n", self->baz.num); break;
    }
}
int main() {
    tagged_union_t tu = { .tag = TAG_FOO, .foo = {.num = 10}};
    tagged_union_print(&tu);

    tu.tag = TAG_BAR;
    tu.bar = (bar_t){ .num = 20};
    tagged_union_print(&tu);

    tu.tag = TAG_BAZ;
    tu.baz = (baz_t){ .num = 30};
    tagged_union_print(&tu);
    return 0;
}

/* O/P: 
    Foo 10
    Bar 20
    Baz 30
*/

//-----------------Using std::variant ans std::visit------------------//

#include <iostream>
#include <variant>
#include <cstdint>

struct Foo {
    uint8_t num{};
    void print() {
        std::cout << "Foo " << (int)num << std::endl;
    }
};
struct Bar {
    uint16_t num{};
    void print() {
        std::cout << "Bar " << num << std::endl;
    }
};
struct Baz {
    uint32_t num{};
    void print() {
        std::cout << "Baz " << num << std::endl;
    }
};

int main() {
    std::variant<Foo, Bar, Baz> v;
    v = Foo{10};
    std::visit([](auto& inner){
        inner.print(); }, v);   // prints: Foo 10
    v = Bar{20};
    std::visit([](auto& inner){
        inner.print(); }, v);   // prints: Bar 20
    v = Baz{30};
    std::visit([](auto& inner){
        inner.print(); }, v);   // prints: Baz 30
}
