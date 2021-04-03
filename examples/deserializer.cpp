#include <simple_json.h>
#include <fstream>

using namespace simple_json::types;
using namespace simple_json::deserializer;

int main() {

    // Loads serialized Json string
    std::string str {R"({"foo": "bar"})"};
    Json json1 (loads(str));

    // Loads serialized Json file.
    Json json2 (load("../example.json"));

    // Loads serialized Json file from ifstream
    std::ifstream json_file {"../example.json"};
    Json json3 (load(json_file));
    if (json_file.is_open()) {
        json_file.close();
    }

    return 0;
}