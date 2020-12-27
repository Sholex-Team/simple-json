#include "simple_json.h"
#include "string"
#include <iostream>

using namespace simple_json;
using namespace types;
using namespace deserializer;

int main() {
    std::string test_json {R"([1, 2, 3, [1, 2, 3, [1, 2, 3]]])"};
    Json loaded(loads(test_json));
    std::cout << loaded << std::endl;
    return 0;
}
