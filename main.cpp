#include "simple_json/simple_json.h"

using namespace simple_json::types;
using namespace simple_json::deserializer;

int main() {
    Json a(loads(R"({"a": 10})"));
    Json b(loads(R"({"a": 15})"));
    a.get_diff(b);
    return 0;
}