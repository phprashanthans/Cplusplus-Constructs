/* RAII: Resource Acquistion Is Initialization - is a programming concept
   in C++ that links resource management like memory, file handles, and network 
   connections to the lifespan of objects. When implemented correctly, RAII
   improves resource safety and helps prevent leaks and undefined behaviors.
   However, vulnerabilities still arise if the RAII pattern is misapplied
   or misunderstood.
*/

#include <iostream>
#include <memory>

class Resource {
    public:
        Resource() { std::cout << "Resource acquired" << std::endl; }
        ~Resource() { std::cout << "Resource released" << std::endl; }
        void doWork() {
            std::cout << "Doing Work" << std::endl;
            #ifdef EXCEPTION_SAFETY
            throw std::runtime_error("Error occured during work");
            #endif
        }
        Resource(const Resource&) = delete;
        Resource& operator=(const Resource&) = delete;
};

#ifdef NO_MEMORY_LEAK
void useResource() {
    Resource res;    // Resource acquired
    res.doWork();    // Do some work
    // Resource is automatically released when 'res' goes out of scope
}
int main() {
    // No memory leak here; Resource is properly managed.
    useResource();
    return 0;
}
#endif
#ifdef CONDITIONAL_AQUISITION
void useResource(bool flag) {
    Resource* res = nullptr;
    if (flag) 
        res = new Resource();  // Manual management, potential leak
    if (res) {
        res->doWork();
        delete res;  // Must remember to delete
    } else {
        std::cout << "Resource not acquired" << std::endl;
    }
}
int main() {
    useResource(true);
    useResource(false);
    return 0;
}
#endif
#ifdef EXCEPTION_SAFETY
void useResource() {
    Resource res;    // RAII manages resource
    res.doWork();    // Exception might be thrown
}
int main() {
    try {
        useResource();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
#endif
#ifdef OVERSIGHTS
void useResource() {
    Resource res;    // Resource acquired
    res.doWork();    // Do some work
    // Resource res2 = res;  // Copying is disabled
    // Resource res3;
    // res3 = res2;   // Assignment is disabled
    // Resource is automatically released when 'res' goes out of scope
}
int main() {
    // No memory leak here; Resource is properly managed.
    useResource();
    return 0;
}
#endif
/* O/P: 
*/
