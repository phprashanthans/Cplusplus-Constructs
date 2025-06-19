/*----------------------------------------------------------------------------------
Splitting interfaces and implementations using variadic template inheritance
One very elegant technique to split access to a concrete implementation class 
is by combining:
- Interfaces (pure virtual classes) to define capabilities
- Variadic template inheritance to combine multiple capabilities into one class flexibly
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class IWriteResource {
    public:
        virtual void write(const std::string& data) = 0;
};

class IReadResource {
    public:
        virtual std::string read() const = 0;
};

template<typename T, typename... Args>
class BaseResource : public Args... {
    public:
        virtual ~BaseResource() = default;
    protected:
        std::string _resource;
};

class ResourceJSON : public BaseResource<ResourceJSON, IWriteResource, IReadResource> {
    public:
        void write(const std::string& data) override {
            _resource = "{ \"data\": \"" + data + "\" }";
        }
        std::string read() const override{
            return _resource;
        }
};

class ResourceXML : public BaseResource<ResourceXML, IWriteResource, IReadResource> {
    public:
        void write(const std::string& data) override {
            _resource = "<data>" + data + "</data>";
        }
        std::string read() const override{
            return _resource;
        }
};

int main() {
    ResourceJSON jsonResource;
    ResourceXML xmlResource;

    std::vector<IWriteResource*> writers = {&jsonResource, &xmlResource}; // have access only to write
    std::vector<IReadResource*> readers  = {&jsonResource, &xmlResource}; // have access only to read

    std::for_each(writers.begin(), writers.end(), [](auto writer) {
        writer->write("Hello World!");
    });
    std::for_each(readers.begin(), readers.end(), [](auto reader) {
        std::cout << reader->read() << std::endl;
    });
    return 0;
}

// Output
// { "data": "Hello World!" }
// <data>Hello World!</data>
