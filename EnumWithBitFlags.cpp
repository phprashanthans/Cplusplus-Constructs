/*---------------------------------------------------------------------------------
Enum with Bit Flags
----------------------------------------------------------------------------------*/
#include <iostream>

// Define an enum with bit flags
enum class FileOptions : unsigned int {
    None    = 0,            // No options
    Read    = 1 << 0,       // 0001 - Read permission
    Write   = 1 << 1,       // 0010 - Write permission
    Execute = 1 << 2,       // 0100 - Execute permission
    Hidden  = 1 << 3        // 1000 - Hidden file attribute
};

// Enable bitwise operations on FileOptions
inline FileOptions operator|(FileOptions a, FileOptions b) {
    return static_cast<FileOptions>(static_cast<FileOptions>(a) | static_cast<FileOptions>(b));
}

inline FileOptions operator&(FileOptions a, FileOptions b) {
    return static_cast<FileOptions>(static_cast<FileOptions>(a) & static_cast<FileOptions>(b));
}

// Function that takes bitwise flags
void openFile(FileOptions options) {
    std::cout << "Opening file with options:\n";
    if ((options & FileOptions::Read)) {
        std::cout << " - Read\n";
    }
    if ((options & FileOptions::Write)) {
        std::cout << " - Write\n";
    }
    if ((options & FileOptions::Execute)) {
        std::cout << " - Execute\n";
    }
    if ((options & FileOptions::Hidden)) {
        std::cout << " - Hidden\n";
    }
}

int main() {
    // Combine with multiple options
    FileOptions options = FileOptions::Read | FileOptions::Write | FileOptions::Hidden;
    // Call function with combined flags
    openFile(options);
    return 0;
}

/*----------------------------------------------------------------------------------
----------------------------------------------------------------------------------*/
