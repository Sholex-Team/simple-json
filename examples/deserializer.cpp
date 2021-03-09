#include <simple_json.h>
#include <fstream>

using namespace simple_json::types;
using namespace simple_json::deserializer;

int main() {

    // load as string
    std::string str {R"({"foo": "bar"})"};
    Json json1 (loads(str));

    // load as file with file path
    Json json2 (load("../example.json"));

    // load as file with ifstream object
    std::ifstream json_file {"../example.json"};
    Json json3 (load(json_file));
    if (json_file.is_open()) {
        json_file.close();
    }

    return 0;
}