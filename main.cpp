#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace utils;

int main() {
    std::string s = "reza__mosi__";
    auto splitted = split(s, "__");
    for (auto slice: splitted) {
        std::cout << slice << std::endl;
    }
    return 0;
}
