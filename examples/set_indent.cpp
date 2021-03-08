#include <simple_json.h>

using namespace simple_json;
using namespace ::types;
using namespace ::deserializer;
using namespace ::indent;

int main() {
    Json json(loads(R"({
        "foo": "bar"
    })"));
    std::cout << set_indent() << json << std::endl;
    std::cout << unset_indent() << json << std::endl;
    return 0;
}