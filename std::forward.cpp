/* Perfect Forwarding: std::forward is used to forward the callable entity while
preserving its value category (lvalue or rvalue). This is a part of perfect
forwarding to avoid unnecessary copies when passing the callable to function
*/

#include <iostream>

template <typename T>
class Value {
    public:
        explicit Value(T value) : value_(std::move(value)) {}

        // The template parameter is Callable here that represent any callable entity such
        // as function, lambda or functor. The && with parameter allows both lvalues and 
        // rvalues of type Callable to be passed.
        template<typename Callable>
        auto apply(Callable&& func) const -> decltype(auto) {
            // decltype(auto) ensures that return type is preserved, whether it's a value or
            // a reference. 
            return std::forward<Callable>(func)(value_);
        }
    private:
        T value_;
};

int main() {
    Value<int> v(25);
    auto result = v.apply([](int val){ return val*val; });
    std::cout << "Result:" << result << std::endl;
    return 0;
}

/* O/P: 
*/
