#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace types;
using namespace serializer;
using namespace types::exceptions;
using namespace serializer::exceptions;

int main() {
    Json a {1, 2, 3};
    for (auto & element: a) {
        std::cout << element << std::endl;
    }
    for (Json::iterator it {a.begin()}; it != a.end(); ++it) {
        std::cout << * it << std::endl;
    }
    return 0;
}
