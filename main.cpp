#include "simple_json.h"
#include "string"

using namespace simple_json;
using namespace types;
using namespace deserializer;

int main() {
    Json test {{"test"_json_key, 15}, {"test_2"_json_key, 16}};
    std::string test_json {"[1, 2, 3]"};
    loads(test_json);
    return 0;
}
