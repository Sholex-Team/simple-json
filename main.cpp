#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace utils;

int main() {
    auto a = split("ad__fn", "_");
    for (auto aa: a) {
        std::cout << aa << std::endl;
    }
    return 0;
}
