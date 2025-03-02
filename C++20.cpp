/*----------------------------------------------------------------------------------
C++20
1) Concepts
2) Ranges
3) Coroutines
4) Three-way Comparison
5) New Standard Library Features
-----------------------------------------------------------------------------------*/

// 1) Concepts: With the advent of templates in C++, writing generic code has been made
// easier, but it also comes with its own set of challenges, such as unclear error messages
// limited type constraints and complex workarounds like SFINAE. Concepts are designed
// to address these challenges by providing a way to express type constraints in a clear
// and intuitive manner. This allow us to define requirements for template parameters,
// thus improving type safety and debugging capabilities.
// Concepts are a way to describe what a type must do to be used in a template, and 
// this allows for better type checking at compile time. 
// In essence, concept is a predicate that checks whether a type satisfies a set of 
// conditions or requirements. A concept is essentially a constraints that you can
// apply to a template type, ensuring that the template operates only on types that
// meet those conditions.

#include <iostream>
#include <iterator>

// Concept to check if a type is iterable; Checks whether a type T has the begin() and end()
// member functions and whether the return types of these functions a forward iterator
template <typename T>
concept Iterable = requires(T t) {
    { begin(t) } -> std::forward_iterator;   // Check for 'begin' function returning forward iterator
    { end(t) } -> std::forward_iterator;     // Check for 'end' function returning forward iterator
};

// The following function is constrained to only accept types that satisy the Iterable concept,
// meaning it can operate on container that provide begin() and end() functions.
template <Iterable T>
void print(T& container) {
    for(auto& elem : container) {
        std::cout << elem << ' ';
    }
}

// Concept for checking if a type supports additions; It checks whether the type T
// supports additions and the result of operation must also be of type T. 
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

// Function template constrained by the Addable concept
template <Addable T>
T add(T a, T b) {
    return a + b;
}

// Concept to check if a type is an integral type
template <typename T>
concept Integral = std::is_integral_v<T>;

// Class template constrained by the Integral concept; IntegerOperations will 
// only be instantiated if T is an integral type, such as int, short or long.
// For non-integral type like double, the compiler will issue an error.
template <Integral T>
class IntegerOperations {
    public:
        T add(T a, T b) {
            return a + b;
        }
};

// 2) A range represents a sequence of elements that can be traversed or manipulated,
// much like an array or container. However unlike traditional containers, ranges are
// not tied to a specific container type, meaning they can refer to any sequence of 
// elements.
// A range is a view or a container. While containers hold their own data and manage
// memory, views are light-weight, non-owning abstractions that represent or transform
// ranges without modifying the original data.

#include <ranges>
#include <vector>
#include <iostream>
#include <numeric>
#include <functional>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};
    // Creating a view that transforms each element by multiplying by 2
    // transformed is a view over data, where each element is lazily transformed.
    // No new memory is allocated for the transformation and the operation is only
    // applied when we iterate over transformed
    auto transformed = data | std::views::transform([](int n) {
        return n * 2;
    });
    for (int n : transformed) {
        std::cout << n << " ";  // Output: 2 4 6 8 10
    }

    // Create a filter view to select even numbers. Again, no memory is
    // allocated and the filter is applied lazily
    auto evens = data | std::views::filter([](int n) { 
        return n % 2 == 0;
    });
    for (int n : evens) {
        std::cout << n << " ";  // Output: 2 4 6
    }

    // Chain views: Filter even numbers and then square them.
    // The composition is lazy and efficient as no intermediate data structures are created
    auto result = data | std::views::filter([](int n) {
        return n % 2 == 0;
    }) | std::views::transform([](int n) {
        return n * n;
    });
    for (int n : result) {
        std::cout << n << " ";  // Output: 4 16
    }

    // std::ranges::find - finds the first element that satisfies a given condition
    // Find the first element greater than 3
    auto res = std::ranges::find(data, 4);
    if (res != data.end()) {
        std::cout << "Found: " << *res << std::endl; // Output: Found: 4
    }

    // std::ranges::sort - sorts a range of elements in ascending order
    std::ranges::sort(data);
    for (int n : data) {
        std::cout << n << " ";  // Output: 1 2 3 4 5
    }

    // std::ranges::accumulate - calculates the sum of a range's elements
    int sum = std::accumulate(data.begin(), data.end(), 0);
    std::cout << "Sum: " << sum << std::endl;  // Output: Sum: 15
}

//3) Coroutines: A special type of function that allows its execution to be paused (or
// suspended) at one point and then resumed later. Unlike regular functions, which 
// execute from start to finish in a single call, coroutines allow a function to yield 
// control back to the caller, resume at a later time, and perform additional work in a
// non-blocking manner.
// The key benefit of corotines is that they provide a mechnaism for writing asynchronous
// code that looks and behaves like synchronous code. This allows developers to write
// code for operations that would typically require callbacks or threads, such as networking,
// file I/O or event handling,
// Coroutines are particularly useful for non-blocking asynchronous operations, which allows
// other tasks to continue while waiting for an operation to complete, such as fetching data
// from a database, performing network requests, or waiting for user input.

#include <iostream>
#include <coroutine>
#include <thread>
#include <chrono>
#include <future>

// 3.1) co_return Keyword

struct async_task {
    struct promise_type {
        async_task get_return_object() {
            return async_task(this);
        }
        std::suspend_always initial_suspend() { return {}; }  // Suspend immediately
        std::suspend_always final_suspend() noexcept { return {}; } // Suspend after completion
        void return_value(int value) {
            result = value;
        }
        void unhandled_exception() {
            std::cerr << "Exception occurred!" << std::endl;
        }
        int result = 0;
    };
    using handle_type = std::coroutine_handle<promise_type>;
    handle_type h;
    async_task(promise_type* p) : h(handle_type::from_promise(*p)) {}
    ~async_task() {
        if (h) h.destroy();
    }
    int get_result() {
        return h.promise().result;
    }
};
async_task example_coroutine() {
    std::cout << "Coroutine started!" << std::endl;

    // Simulate a suspension
    std::this_thread::sleep_for(std::chrono::seconds(2));

    co_return 42;  // Return a value after sleeping
}

int main() {
    auto task = example_coroutine();  // Start the coroutine
    std::this_thread::sleep_for(std::chrono::seconds(3));  // Wait for the coroutine to finish
    std::cout << "Coroutine result: " << task.get_result() << std::endl;
    return 0;
}

// 4) Three-way comparison operator (Spaceship Operator <==>)
// Unifies multiple comparison operations into a single operator.
// The return type of the <=> operator can be one of several comparisons categories:
// std::strong_ordering: For strict ordering where the result is either less than, equal to, or greater than.
// std::weak_ordering: For weaker ordering where comparison might include indeterminate states (NaN comparisons in FPU)
// std::partial_ordering: For cases where comparisons might not always be meaningful or defined (comparing std::optional values)

#include <iostream>
#include <compare>
struct Point {
    int x;
    int y;

    // Default implementation of the spaceship operator
    std::strong_ordering operator<=> (const Point& other) const = default;
};

int main() {
    Point obj1{1, 2};
    Point obj2{2, 3};

    if(obj1 < obj2) {
        std::cout << "obj1 is less than obj2" << std::endl;
    } else if (obj1 == obj2) {
        std::cout << "obj1 is equal to obj2" << std::endl;
    } else {
        std::cout << "obj1 is greater than obj2" << std::endl;
    }
    return 0;
}

// 5) New Standard Library Features: std::span and std::format
// 5.1) std::span - A safer and more flexible array view
// It is a lightweight, non-owning and bound checked  view of a contiguous 
// sequence of objects. It can represent arrays, portions of array, or 
// sections of a container like a std::vector or std::array

#include <span>
#include <iostream>
#include <vector>

void print_span(std::span<int> sp) {
    for (auto& val : sp) {
        std::cout << val << " ";
        val = val * 2;  // Modifies each element (e.g. double it) without copying
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::span<int> sp(arr);  // Create a span from a C-style array without copying its contents
    print_span(sp);  // Passing span to a function

    std::vector<int> vec = {6, 7, 8, 9, 10};
    std::span<int> sp_vec(vec);  // Create a span from a std::vector
    print_span(sp_vec);

    std::span<int> subrange = sp.subspan(1, 3);  // Extracts elements from index 1 to 3 (2, 3, 4)
    print_span(subrange);  // Output: 2 3 4

    return 0;
}

// 5.2) std::format - Modern, Type-Safe String Formatting
// It is type safe, improves readability and highly efficient and maintainable code
// For integers {} - Default formatting,
//              {:.2} - Limits to 2 digits
//              {:x} - Format as hexadecimal
// For Floating Point numbers {:.2f} - Fixed Point notation
//                            {:.2e} - Scientific notation
// For strings: {:<10} - Left align within a field of width 10
//              {:>10} - Right align
// For date & time: {:%Y-%m-%d} - Format a date as "YYYY-MM-DD"
#include <format>
#include <iostream>

int main() {
    int value = 42;
    double pi = 3.14159;
    std::string name = "Alice";

    // Format a string with placeholders
    std::string result = std::format("Hello, {}! The value of pi is {:.2f}.  \\
    You are {} years old.", name, pi, value);
    std::cout << result << std::endl;  // Output: Hello, Alice! The value
    // of pi is 3.14. You are 42 years old.
    return 0;
}
