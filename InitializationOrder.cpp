/*----------------------------------------------------------------------------------
The order of member initialization is crucial. 
In reality, the order of member initialization follows the order of declaration in 
the struct, not the order in the initializer list. So, what happens:alignas
    1. ref is initialized before val, because ref is declared first in the struct
    2. At the time ref(val) is evaluated, val is uninitialized
    3. Then val is initialized with v
So, ref ends up binding to an uninitialized val, and will not reflect changes to val.
The correct solution would be to reorder the struct members
struct S {
    int val;
    int& ref;
}
-----------------------------------------------------------------------------------*/
#include <iostream>
struct S {
    int& ref;
    int val;

    S(int v) : ref(val), val(v) {}
    void print() const {
        std::cout << "val = " << val << ", ref = " << ref << "\n";
    }
};

int main() {
    S s(42);
    s.print();
    return 0;
}
