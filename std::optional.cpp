/* std::optional ==> It represents an object that may or may not hold a value.
This is useful for handling functions that may or may not return a meaningful
result.
You can initialize a data variable with a std::optional
std::optional<int> opt = std::nullopt;
int value = opt.has_value()     // Returns if opt has any value
int value = opt.value_or(10);   // Returns 10 if opt has no value.
*/
#include <iostream>
#include <optional>

// General Interface
template<typename T>
class IValue {
    public:
        virtual ~IValue() = default;
    public:
        virtual T get() const = 0;
};
// Implementation for raw values
template<typename T> 
class RawValue : public IValue<T> {
    public:
        explicit RawValue(T value) : m_value(std::move(value)) {}
    public:
        T get() const override {
            return m_value;
        }
    private:
        T m_value;
};
// Implementation for std::optional
template<typename T>
class OptionalValue: public IValue<T> {
    public:
        explicit OptionalValue(std::optional<T> value) : m_value(std::move(value)) {}
    public:
        T get() const override {
            return m_value.value();
        }
    private:
        std::optional<T> m_value;
};

int main() {
    auto values = std::vector<std::unique_ptr<IValue<int>>>();
    values.push_back(std::make_unique<RawValue<int>>(10));
    values.push_back(std::make_unique<OptionalValue<int>>(15));
    values.push_back(std::make_unique<RawValue<int>>(20));

    for(const auto& v : values) {
        std::cout << v->get() << std::endl;
    }
}
