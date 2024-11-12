/* With C++20, one of the powerful tool for metaprogramming - concepts
With concepts, you can explicitly define what type a template function
or class expects. This helps not only with enforcing constraints but
also improves compiler messages.
*/
#include <iostream>
#include <string>
#include <concepts>

template <typename T>
concept DuckConcept = requires(T a) {
    {a.say_quack()} -> std::same_as<std::string>;
    {a.walk_like_a_duck()} -> std::same_as<void>;
};

class Duck {
    public:
        std::string say_quack() const {
            return "Quack";
        }
        void walk_like_a_duck() const {
            std::cout << "Duck is walking" << std::endl;
        }
};
class RoboDuck {
    public:
        std::string say_quack() const {
            return "Robo quack";
        }
        void walk_like_a_duck() const {
            std::cout << "Robo Duck is walking" << std::endl;
        }
};
// The two classes above have no relation to each other but satisfy the concept.
// The following function can use the concept as template parameter
template <DuckConcept T>
void walk_and_quack(const T& duck) {
    std::cout << "Quack: " << duck.say_quack() << std::endl;
    duck.walk_like_a_duck();
}

int main()
{
    auto duck = Duck();
    walk_and_quack(duck);
    
    auto roboDuck = RoboDuck();
    walk_and_quack(roboDuck);

    return 0;
}
