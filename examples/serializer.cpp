#include <simple_json.h>
#include <string>

using namespace simple_json::types;
using namespace simple_json::serializer;

int main() {
    Json json {
            {"foo"_json_key, "bar"}
    };

    // Serializes Json object into a std::string
    std::string str {dumps(json)};

    // Serializes Json object into a file
    dump(json, "example.json", 2);

    // Serializes Json object into a file using ofstream
    std::ofstream json_file {"example1.json"};
    dump(json, json_file);
    if (json_file.is_open()) {
        json_file.close();
    }
    return 0;
}