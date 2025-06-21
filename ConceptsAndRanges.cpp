/*-----------------------------------------------------------------------------------
With concepts and ranges, we can define expected container properties, and if the user
violates them, they get a clear error instead of template hell.
The ranges library provides several useful concepts:
- std::ranges::range -> Type has just begin() and end()
- std::ranges::sized_range -> Range that provides a size() method
- std::ranges::input_range, std::ranges::output_range etc -> Define specific iterator rqms

Additionally, we can extract information about a range using these 𝐭𝐫𝐚𝐢𝐭𝐬: 
 - 𝚜𝚝𝚍::𝚛𝚊𝚗𝚐𝚎𝚜::𝚒𝚝𝚎𝚛𝚊𝚝𝚘𝚛_𝚝<𝚃> → Iterator type. 
 - 𝚜𝚝𝚍::𝚛𝚊𝚗𝚐𝚎𝚜::𝚌𝚘𝚗𝚜𝚝_𝚒𝚝𝚎𝚛𝚊𝚝𝚘𝚛_𝚝<𝚃> → Const iterator type. 
 - 𝚜𝚝𝚍::𝚛𝚊𝚗𝚐𝚎𝚜::𝚛𝚊𝚗𝚐𝚎_𝚟𝚊𝚕𝚞𝚎_𝚝<𝚃> → Value type of the range.
 - 𝚜𝚝𝚍::𝚛𝚊𝚗𝚐𝚎𝚜::𝚛𝚊𝚗𝚐𝚎_𝚜𝚒𝚣𝚎_𝚝<𝚃> → Size type (for sized ranges). 
-----------------------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <ranges>

template<std::ranges::input_range C>
std::size_t count (const C& container, const std::ranges::range_value_t<C>& value) {
    std::size_t res = 0;
    for (const auto& element : container) {
        if (element == value) {
            res += 1;
        }
    }
    return res;
}

int main() {
    auto res = count(std::vector{1, 2, 3, 4, 2, 3}, 2);
    std::cout << res << std::endl;
    return 0;
}

/*----------- Output --------------------
2
----------------------------------------*/
