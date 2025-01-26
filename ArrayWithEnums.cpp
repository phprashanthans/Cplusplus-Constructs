/*---------------------------------------------------------------------------------
Make arrays more expressive with enums!
Instead of hardcoded indexes, use enums to make the code more readable and maintainable
----------------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <format>

enum Columns { 
    CityName,
    Population,
    AverageTemperature,
    NumberOfColumns
};

// Print table
void printTheTable(const auto& headers, const auto& rows) {
    // Enums are used to print particular header instead of hardcoded indexes
    std::cout << std::format("{:^10}|{:^15}|{:^10}", headers[CityName], headers[Population], headers[AverageTemperature]) << std::endl;

    for(const auto& row : rows) {
        // Enums are used to print particular header instead of hardcoded indexes
        std::cout << std::format("{:^10}|{:^15}|{:^10}", row[CityName], row[Population], row[AverageTemperature]) << std::endl;
    }
    std::cout << "\n";
}

int main() {
    std::array<std::string, NumberOfColumns> headers = {"City Name", "Population", "Average Temperature"};
    std::vector<std::array<std::string, NumberOfColumns>> rows = {
        {"Tokyo", "37.4 million", "15 C"},
        {"Delhi", "29.3 million", "18 C"},
        {"Shanghai", "26.3 million", "16 C"},
    };
    printTheTable(headers, rows);
    rows[0][Population] = "30.1 million";
    printTheTable(headers, rows);
    return 0;
}
/*---------------------------------------------------------------------------------
City Name |  Population   |Average Temperature
  Tokyo   | 37.4 million  |   15 C   
  Delhi   | 29.3 million  |   18 C   
 Shanghai | 26.3 million  |   16 C   

City Name |  Population   |Average Temperature
  Tokyo   | 30.1 million  |   15 C   
  Delhi   | 29.3 million  |   18 C   
 Shanghai | 26.3 million  |   16 C 
----------------------------------------------------------------------------------*/
