#include "deserializer.h"

namespace simple_json::deserializer {
    using Json = simple_json::types::Json;
    using JsonObject = simple_json::types::JsonObject;
    using Array = simple_json::types::Array;
    using DataType = simple_json::types::DataType;

    Json loads(const std::string & json_text) {
        Json main_object {DataType::unknown};
        std::stack<Json *> primary_stack {};
        std::string last_value {};
        std::string last_key {};
        DataType last_type {DataType::unknown};
        bool escaped {false};
        bool finished {false};
        for (char ch: json_text) {
            if (finished) {
                throw exceptions::ParsingException {};
            }
            switch (ch) {
                case '{':
                    if (last_type == DataType::unknown) {
                        if (primary_stack.empty()) {
                            main_object = DataType::json_object_type;
                            primary_stack.push(& main_object);
                            continue;
                        }
                        if (primary_stack.top()->type() == DataType::json_object_type) {
                            if (!last_key.empty()) {
                                primary_stack.top()->insert({
                                    types::JsonKey {last_key},
                                    Json {DataType::json_object_type}
                                });
                                primary_stack.push(& primary_stack.top()->at(last_key.c_str()));
                                last_key.clear();
                                continue;
                            }
                            throw exceptions::ParsingException {};
                        } else if (primary_stack.top()->type() == DataType::array_type) {
                            primary_stack.top()->push_back({Json {DataType::json_object_type}});
                            primary_stack.push(& primary_stack.top()->back());
                        }
                    } else if (last_type == DataType::string_type) {
                        last_value.push_back(ch);
                    } else if (last_type == DataType::string_key) {
                        last_key.push_back(ch);
                    } else {
                        throw exceptions::ParsingException {};
                    }
                    break;
            }
        }
        return std::move(main_object);
    }
}
