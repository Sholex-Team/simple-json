#include "simple_json.h"

using namespace simple_json;

int main() {
    types::Json a {
            {"t5"_json_key, 5},
            {"names"_json_key, {"Ali", "Ahmad", "Reza", {{"test"_json_key, 5}}}},
    };
    try {
        serializer::dump(a, "test.json", 3);
        serializer::dump(a, "/home/antiwanted/Desktop/test.json");
    } catch (exceptions::WritingToFileException & e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
