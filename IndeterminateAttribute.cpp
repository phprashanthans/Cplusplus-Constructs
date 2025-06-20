/*-----------------------------------------------------------------------------------
Erroneous Behavior: A well-defined but conceptually incorrect behavior
[[indeterminate]] attribute allows developers to explicitly leave a variable
unitialized when that is the intended behaviour
-----------------------------------------------------------------------------------*/
#include <iostream>

void process(int value) {
    // process the value
}

void handle(int value) {
    // use the value
}

struct Data {
    Data() {} // user-defined constructor
    int field;
};

void use(Data d [[indeterminate]]) {
    handle(d.field);  // undefined behavior: d.field is indeterminate
}

int main() {
    int x;  // Initialized by the implementation, but not explicitly set by the programmer
    int y; [[indeterminate]]  // Intentionally unitialized, using it causes undefined behaviour

    // errorenous behaviour: well-defined, but x was never assigned
    process(x);
    // undefined behaviour: y is indeterminate
    process(y); 

    // passing a default constructed object triggers undefined behaviour
    use(Data());
    return 0;
}

// Output
