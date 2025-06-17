/* In linux, shared libraries are generally loaded automatically by the dynamic loader.
   However for certain case, you may want to load libraries manually. In such cases, the
   application retrieves the address of an entry function from the shared library and then
   uses it to access the required objects. Here is the basic approach for manually loading
   a shared library:
   - dlopen: Loads the shared library
   - dlsym: Obtain the address of the required function
   - dlclose: Close the library when done
*/
#include <iostream>
#include <dlfcn.h>

// hello_func is an alias for a pointer to a function that takes no parameters and returns void.
typedef void (*hello_func)();

int main() {
    // Use a lambda as the deleter for std::unique_ptr
    auto handle = std::unique_ptr<void*, decltype(&dlclose)>(dlopen("./libexample.so", RTLD_LAZY), dlclose);

    if (!handle) {
        std::cerr << "Error loading library: " << dlerror() << std::endl;
        return 1;
    }
    dlerror();
    hello_func hello = static_cast<hello_func>(dlsym(handle.get(), "hello"));
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Error loading symbol 'hello': " << dlsym_error << std::endl;
        return 1;
    }
    hello();
    return 0;
}

/* O/P: 
    
*/
