#include <iostream>
#include "simple_json.h"

using namespace simple_json::types;

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    Json a {
            {"hi"_json_key, {1, 2, 3}},
            {"test"_json_key, "test_2"},
    };
    return 0;
}
