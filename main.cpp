#include "simple_json.h"
#include "string"

using namespace simple_json;
using namespace types;
using namespace deserializer;

int main() {
    Json {{1, 2, 3}};
    std::string test_json {"[1, 2, 3]"};
    loads(test_json);
}
