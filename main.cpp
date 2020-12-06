#include <iostream>
#include <iomanip>
#include "simple_json.h"

using namespace simple_json::types;

int main() {
    JsonObject a {
            {"t"_json_key, 5}
    };
    std::cout << std::setw(5) << a;
    return 0;
}
