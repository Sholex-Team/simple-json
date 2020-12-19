#include "deserializer.h"

namespace simple_json::deserializer {
    using Json = types::Json;
    using JsonObject = types::JsonObject;
    using Array = types::Array;
    using DataType = types::DataType;
    using JsonKey = types::JsonKey;

    Json loads(const std::string & json_text) {
        Json main_object {DataType::unknown};
        std::stack<Json *> primary_stack {};
        std::string last_value {};
        std::string last_key {};
        DataType last_type {DataType::unknown};
        bool escaped {false};
        bool finished {false};
        bool key_split {false};
        bool array_split {false};
        for (char ch: json_text) {
            if (finished) {
                throw exceptions::ParsingException {};
            }
            switch (ch) {
                case '{':
                    switch (last_type) {
                        case DataType::unknown:
                            if (primary_stack.empty()) {
                                main_object = DataType::json_object_type;
                                primary_stack.push(& main_object);
                                continue;
                            }
                            if (primary_stack.top()->type() == DataType::json_object_type) {
                                if (!last_key.empty()) {
                                    primary_stack.top()->insert({
                                        JsonKey {last_key},
                                        Json {DataType::json_object_type
                                        }});
                                    primary_stack.push(& primary_stack.top()->at(last_key.c_str()));
                                    last_key.clear();
                                    continue;
                                }
                                throw exceptions::ParsingException {};
                            } else if (primary_stack.top()->type() == DataType::array_type) {
                                primary_stack.top()->push_back({Json {DataType::json_object_type}});
                                primary_stack.push(& primary_stack.top()->back());
                            }
                        case DataType::string_type:
                            last_value.push_back(ch);
                            continue;
                        case DataType::string_key_type:
                            last_key.push_back(ch);
                            continue;
                        default:
                            throw exceptions::ParsingException {};


                    }
                case '[':
                    if (last_type == DataType::unknown) {
                        if (primary_stack.empty()) {
                            main_object = DataType::array_type;
                            primary_stack.push(& main_object);
                            continue;
                        }
                        if (primary_stack.top()->type() == DataType::json_object_type) {
                            if (!last_key.empty()) {
                                primary_stack.top()->insert({
                                    JsonKey {last_key},
                                    Json {DataType::array_type}
                                });
                                primary_stack.push(& primary_stack.top()->at(last_key.c_str()));
                                last_key.clear();
                            }
                            throw exceptions::ParsingException {};
                        } else if (primary_stack.top()->type() == DataType::array_type) {
                            primary_stack.top()->push_back(Json {DataType::array_type});
                            primary_stack.push(& primary_stack.top()->back());
                        } else {
                            throw exceptions::ParsingException {};
                        }
                    } else if (last_type == DataType::string_type) {
                        last_value.push_back(ch);
                    } else if (last_type == DataType::string_key_type) {
                        last_key.push_back(ch);
                    }
                    break;
                case '"':
                    if (escaped) {
                        if (last_type == DataType::string_type) {
                            last_value.push_back(ch);
                        } else {
                            last_value.push_back(ch);
                        }
                        continue;
                    }
                    switch (last_type) {
                        case DataType::unknown:
                            if (primary_stack.empty()) {
                                last_type = DataType::string_type;
                                continue;
                            }
                            if (primary_stack.top()->type() == DataType::json_object_type) {
                                if (!last_key.empty() && key_split) {
                                    last_type = DataType::string_type;
                                    continue;
                                } else if (last_key.empty() && array_split) {
                                    last_type = DataType::string_key_type;
                                    continue;
                                }
                            } else if (primary_stack.top()->type() == DataType::array_type) {
                                if (last_key.empty() && array_split) {
                                    last_type = DataType::string_type;
                                    continue;
                                }
                            }
                            throw exceptions::ParsingException {};
                        case DataType::string_type:
                            if (primary_stack.empty()) {
                                finished = true;
                                main_object = Json {last_value};
                            }
                            if (primary_stack.top()->type() == DataType::json_object_type) {
                                primary_stack.top()->insert({
                                    JsonKey {last_key},
                                    Json {last_value}
                                });
                                last_value.clear();
                                last_key.clear();
                                last_type = DataType::unknown;
                                key_split = false;
                                continue;
                            } else if (primary_stack.top()->type() == DataType::array_type) {
                                primary_stack.top()->push_back(Json {last_value});
                                last_value.clear();
                                array_split = false;
                                last_type = DataType::unknown;
                                continue;
                            }
                            throw exceptions::ParsingException {};
                        case DataType::string_key_type:
                            if (!last_key.empty()) {
                                key_split = false;
                                last_type = DataType::unknown;
                                continue;
                            }
                            throw exceptions::ParsingException {};
                        default:
                            throw exceptions::ParsingException {};
                }
            }
        }
        return std::move(main_object);
    }
}
