#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace types;
using namespace serializer;
using namespace types::exceptions;
using namespace serializer::exceptions;

int main() {
    Json a {1, 2, 3};
    Json b {{"test"_json_key, 10}};
    for (auto & element: a) {
        std::cout << element << std::endl;
    }
    for (Json::iterator it {a.begin()}; it != a.end(); ++it) {
        std::cout << * it << std::endl;
    }
    for (Json::iterator it {b.begin()}; it != b.end(); ++it) {
        std::cout << "Key is " << it.key() << "\nValue is " << it.value() << std::endl;
    }
    for (auto & [key, value]: b.items()) {
        std::cout << "Key is " << key << "\nValue is " << value << std::endl;
    }
    return 0;
}
