#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace serializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"([1, 2, 3, 6, 4, 7, 11])"));
    Json dst(loads(R"([1, 3, 2, 6, 5, 7])"));
    Json merged(src.merge(dst));
    std::cout << merged << std::endl;
    return 0;
}
