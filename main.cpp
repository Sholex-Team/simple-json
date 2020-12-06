#include <iostream>
#include <iomanip>
#include "simple_json.h"

using namespace simple_json::types;

int main() {
    JsonObject a {
            {"t"_json_key, 5}
    };
    std::cout << a << std::endl;
    return 0;
}
