/*----------------------------------------------------------------------------------
Memory Allocation at Compile-Time in C++
Since C++20, memory can be allocated at compile-time - but with a key rule
"What happens at compile time must stay at compile time."
Heap Allocation (new, delete), STL containers, and smart pointers can be used inside 
constexpr or consteval functions, but not as return values. 
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <array>
#include <vector>

consteval int allocateAtCompileTime() {
    // Memory can be allocated at the compile time
    int* a = new int(10);
    auto res = *a;

    // Compiler will detect if memory isn't de-allocated
    delete a;
    return res;
}

constexpr int* onlyRunTimeAllocation() {
    int* a = new int(10);
    return a;
}

int main() {

    // invoked at compile time
    constexpr auto compileTimeVariable = allocateAtCompileTime();
    // Function returned pointer might be called at runtime
    auto* runtimePointer = onlyRunTimeAllocation();
    delete runtimePointer;

    // The same function is prohibited at compile time 
    // constexpr auto* brockenCompileTime = onlyRunTimeAllocation();

    return 0;
}
