/*---------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <shared_mutex>
#include <mutex>
#include <vector>
#include <thread>
#include <chrono>
#include <syncstream>

class Resource {
    public:
        std::string read() const {
            auto lock = std::shared_lock{mutex};
            return m_data;
        }
        void write(std::string_view data) {
            auto lock = std::unique_lock{mutex};
            m_data = data;
        }
    private:
        std::string m_data{"undefined"};
        mutable std::shared_mutex mutex;
};

int main() {
    auto resource = Resource();
    auto reader = [&resource]() {
        for(int i = 0; i < 10; i++) {
            auto data = resource.read();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::osyncstream (std::cout) << std::this_thread::get_id() << 
                ":" << data << ", iteration:" << i << std::endl;
        }
    };
    auto readers = std::vector<std::jthread>{};
    for(int i=0; i<10; i++) {
        readers.push_back(std::jthread(reader));
    }
    auto writer = std::jthread([&resource]() {
        for(int i = 0; i < 10; i++) {
            auto data = "Write: " + std::to_string(i);
            resource.write(data);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            (std::cout) << std::this_thread::get_id() << 
                ":" << data << ", iteration:" << i << std::endl;
        }
    });
    return 0;
}
