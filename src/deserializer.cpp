
#include "deserializer.h"
#include <string>
#include <stack>

namespace simple_json::deserializer {
    using Json = simple_json::types::Json;
    using JsonObject = simple_json::types::JsonObject;
    using Array = simple_json::types::Array;
    using DataType = simple_json::types::DataType;
    Json loads(const std::string & json_text) {
        std::stack<std::pair<DataType, Json>> primary_stack;
        std::string last_key {};
        for (char ch: json_text) {
            if (ch == '{') {
                primary_stack.push({DataType::json_object_type, Json {JsonObject {}}});
            } else if (ch == '"') {
                primary_stack.push({DataType::string_type, Json {""}});
            } else if (ch == ']') {
                primary_stack.push({DataType::array_type, Json {Array {}}});
            }
        }

    }
}