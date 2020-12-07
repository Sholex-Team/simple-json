#include "simple_json.h"
#include <iostream>
#include <string>

using namespace simple_json;

int main() {
    types::Json a {
            {"t5"_json_key, 5},
            {"names"_json_key, {"Ali", "Ahmad", "Reza", {{"test"_json_key, 5}}}},
    };
    std::string result {serializer::dumps(a)};
    std::cout << result << std::endl;
    return 0;
}
