#include <iostream>
#include <simple_json.h>

using namespace simple_json::types;

int main() {
    Json json {
            {"foo"_json_key, "bar"},
            {"number"_json_key, 1}
    };
    // range base for loop
    std::cout << "Range Base For Loop" << std::endl;
    for (const auto & item: json.items()) {  // auto or pair_type
        std::cout << "key: " << item.first << ", value: " << item.second << std::endl;
    }
    // for loop
    std::cout << "\nFor Loop" << std::endl;
    for (Json::iterator it {json.begin()}; it != json.end(); ++it) { // or use const_iterator and cbegin, cend
        std::cout << "key: " << it.key() << ", value: " << it.value() << std::endl;
    }
    return 0;
}
