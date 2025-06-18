/*-----------------------------------------------------------------------------------
1. glvalue (Generalized Lvalue)
    An expression that identifies an object or function, which occupies a specific memory 
    location.
2. lvalue (Locator value)
    A glvalue that refers to a named object or has a persistent identity
3. xvalue (eXpiring value)
    A glvalue that refers to resources that can be reused (typically temporary
    objects that are about to expire)
4. prvalue (Pure rvalue)
    A temporary value that does not identify an object with a memory location
5. rvalue (Right value)
    Anything you can't assign to (i.e. not lvalue)
    rvalue = prvalue + xvalue
-----------------------------------------------------------------------------------*/
#include <iostream>

int main() {
    /*-----------GLValue-------------------*/
    int x = 10;
    x;          // glvalue
    (x+2) = 5;  // Error: (x+2) is not a glvalue
    int& ref = x;
    ref;       // glvalue
    /*-------------LValue------------------*/
    int a = 5;
    a;           // lvalue
    int* p = &a; // a is an lvalue
    /*-------------XValue------------------*/
    std::string get();
    std::move(get());  // xvalue
    std::move(str);    // xvalue: str is about to be moved
    /*-------------PRValue------------------*/
    5;                  // prvalue;
    1+2;                // prvalue;
    std::string("hi");  // prvalue
    /*--------------RValue------------------*/
    10;                 // prvalue -> rvalue
    std::move(x);       // xvalue -> rvalue
    return 0;
}

/*------------------------------------------------------
lvalue has identity, not movable (without std::move)
prvalue has no identity, movable (implicitly)
xvalue has identity, movable
glvalue = anything with identity (lvalue or xvalue)
rvalue = anything that is movable (prvalue, xvalue)

             Expression
                  |
        +-------------------+
        |                   |
     glvalue              rvalue
     /    \               /    \
lvalue    xvalue      xvalue  prvalue
-------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
Example
-----------------------------------------------------------------------------------*/
#include <iostream>

struct SomeType {
    int value;
};
void someFuncWithRValueParam(SomeType&& some_object) {}

// lvalue: has identity and not movable
// xvalue: has identity and movable
// prvalue: has no identity and movable
// glvalue: has identity (lvalue + xvalue)
// rvalue: movable (xvalue + prvalue)

int main() {
    // 'some_object' is lvalue
    SomeType some_object{};
    // so it can be bound to an lvalue reference
    SomeType& lref{some_object};

    // std::move(some_object) is an xvalue
    std::move(some_object);
    // cannot use moved-from object later, so reinitializing it
    some_object = SomeType{};
    // 'std::move(some_object)' is an xvalue
    // so it can be bound to an rvalue reference
    SomeType&& xref{std::move(some_object)};

    // 'SomeType{42}' is a prvalue
    SomeType{42};
    // so it can be bound to an rvalue reference
    SomeType&& prref{SomeType{42}};

    // 'xref' and 'prref' are lvalues
    // because they can appear on left side of assignments
    xref = SomeType{420};
    // so the following won't compile
    // someFuncWithRValueParam(xref);
    // we should move from it, then it get compiled
    someFuncWithRValueParam(std::move(xref));
    return 0;
}

