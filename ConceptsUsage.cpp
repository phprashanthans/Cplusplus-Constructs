/*----------------------------------------------------------------------------------
Concepts aim to improve how Templates are used, making them safer and easier to work
with. Introduced with C++20
-----------------------------------------------------------------------------------*/
#include <iostream>

// There is no clarification that T must support the addition operation. If an unsupported type
// (e.g. std::string with int) is passed, you will get complex and hard-to-understand errors
template <typename T>
T add(T a, T b) {
    return a + b;
}

// With Concepts, which are used to clarify that T must be a numeric type. Less error prone code.
template <typename T>
requires std::integral<T> || std::floating_point<T>
T add(T a, T b) {
    return a + b;
}

// With SFINAE (Without Concepts) Complex technique and hard to read complex code
template <typename T, typename = std::enable_if<std::is_integral_v<T>>>
T add(T a, T b) {
    return a + b;
}

// Template which expects the supported type T to have a specific function (e.g. size()),
// Concepts allow you to verify this at compile-time.
template <typename T>
requires requires(T t) { t.size(); }
void printSize(T t) {
    std::cout << t.size() << std::endl;
}

// Specify the exact requirements that types used with Templates must meet, making the code 
// more robust and scalable
template<typename T>
concept Drawable = requires(T t) {
    t.draw();
};
template <Drawable T>
void render(T shape) {
    shape.draw();
}

int main() {
    return 0;
}
/*-----------------------------------------------------------------------------------
------------------------------------------------------------------------------------*/


#include <iostream>

template <typename T>
concept Printable = requires(T value) {
    {std::cout << value } -> std::same_as<std::ostream&>;
};

void Print(Printable auto const& value) {
    std::cout << value << std::endl;
}

int main() {
    Print("Hello, Concepts!");
    return 0;
}






