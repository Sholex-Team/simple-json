#include "simple_json.h"

using namespace simple_json;
using namespace types;
using namespace serializer;
using namespace types::exceptions;
using namespace serializer::exceptions;

int main() {
    Json a {
            {"t5"_json_key, 5},
            {"names"_json_key, {"Ali", "Ahmad", "Reza", {{"test"_json_key, 5}}}},
    };
    try {
        dump(a, "../test.json", 3);
        dump(a, "../test-without-indent.json");
    } catch (WritingToFileException & e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
