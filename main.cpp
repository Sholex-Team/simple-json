#include "simple_json.h"
#include "string"

using namespace simple_json;
using namespace types;
using namespace deserializer;

int main() {
    std::string test_json {"[1, 2, 3]"};
    Json loaded(loads(test_json));
    return 0;
}
