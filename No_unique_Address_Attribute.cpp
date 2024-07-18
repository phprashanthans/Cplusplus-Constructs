#include <iostream>
using namespace std;

// [[no_unique_address]]
// Non static data members annotated with this attribute 
// are permitted to overlap with other members or base class

struct Empty {};
struct HasMember {
    int m;
};

template <typename Member>
struct Basic {
    Member m;
    int v;
};

template <typename Member>
struct Compressed {
    [[no_unique_address]] Member m;
    int v;
};

template <typename Member>
struct MaybeEmpty {
    [[no_unique_address]] Member m;
};

int main()
{
    cout << sizeof(Basic<Empty>) << endl;            // 8 [(1+3) + 4]  includes padding
    cout << sizeof(Basic<HasMember>) << endl;        // 8 [4 + 4]
    cout << sizeof(Compressed<Empty>) << endl;       // 4 [0 + 4]
    cout << sizeof(Compressed<HasMember>) << endl;   // 8 [4 + 4]
    cout << sizeof(MaybeEmpty<Empty>) << endl;       // 1
    cout << sizeof(MaybeEmpty<HasMember>) << endl;   // 4
    return 0;
}
