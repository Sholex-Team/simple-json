#include "deserializer.h"

namespace simple_json::deserializer {
    using Json = types::Json;
    using DataType = types::DataType;
    using JsonKey = types::JsonKey;

    Json loads(const std::string & json_text) {
        Json main_object(DataType::unknown);
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
            if (ch == '}' || ch == ']' || ch == ',') {
                if (last_type == DataType::integer_type || last_type == DataType::double_type) {
                    if (last_type == DataType::integer_type) {
                        long int integer_value {strtol(last_value.c_str(), nullptr, 10)};
                        if (primary_stack.top()->type() == DataType::array_type) {
                            primary_stack.top()->push_back(integer_value);
                        } else {
                            primary_stack.top()->insert({JsonKey {last_key}, integer_value});
                            last_key.clear();
                        }
                    } else {
                        double double_value {strtod(last_value.c_str(), nullptr)};
                        if (primary_stack.top()->type() == DataType::array_type) {
                            primary_stack.top()->push_back(double_value);
                        } else {
                            primary_stack.top()->insert({JsonKey {last_key}, double_value});
                            last_key.clear();
                        }
                    }
                    last_value.clear();
                }
            }
            switch (ch) {
                case '}':
                    if (primary_stack.top()->type() == DataType::json_object_type && last_type == DataType::unknown) {
                        primary_stack.pop();
                        if (primary_stack.empty()) {
                            finished = true;
                        }
                        continue;
                    }
                    throw exceptions::ParsingException {};
                case ']':
                    if (primary_stack.top()->type() == DataType::array_type && last_type == DataType::unknown) {
                        primary_stack.pop();
                        if (primary_stack.empty()) {
                            finished = true;
                        }
                        continue;
                    }
                    throw exceptions::ParsingException {};
                case ',':
                    if (!key_split && !array_split) {
                        if (last_type == DataType::unknown) {
                            array_split = true;
                        }
                        continue;
                    }
                    throw exceptions::ParsingException {};
                case ':':
                    if (last_type == DataType::unknown) {
                        if (!key_split && !array_split && !last_key.empty()) {
                            key_split = true;
                            continue;
                        }
                        throw exceptions::ParsingException {};
                    }
                    if (last_type == DataType::string_key_type)
                        last_key.push_back(ch);
                    else if (last_type == DataType::string_type)
                        last_value.push_back(ch);
                    else
                        throw exceptions::ParsingException {};
                case '\\':
                    if (last_type == DataType::string_key_type || last_type == DataType::string_type) {
                        escaped = true;
                        continue;
                    }
                    throw exceptions::ParsingException {};
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
                                        Json(DataType::json_object_type)
                                    });
                                    primary_stack.push(& primary_stack.top()->at(last_key.c_str()));
                                    last_key.clear();
                                    continue;
                                }
                                throw exceptions::ParsingException {};
                            } else if (primary_stack.top()->type() == DataType::array_type) {
                                primary_stack.top()->push_back(Json(DataType::json_object_type));
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
                                    Json(DataType::array_type)
                                });
                                primary_stack.push(& primary_stack.top()->at(last_key.c_str()));
                                last_key.clear();
                            }
                            throw exceptions::ParsingException {};
                        } else if (primary_stack.top()->type() == DataType::array_type) {
                            primary_stack.top()->push_back(Json(DataType::array_type));
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
                        if (last_type == DataType::string_type)
                            last_value.push_back(ch);
                        else
                            last_key.push_back(ch);
                        escaped = false;
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
                                    key_split = false;
                                    continue;
                                } else if (last_key.empty() && array_split) {
                                    last_type = DataType::string_key_type;
                                    array_split = false;
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
                case '-':
                    if (last_type == DataType::unknown) {
                        last_type = DataType::integer_type;
                        last_value.push_back(ch);
                        continue;
                    } else if (last_type != DataType::string_type && last_type != DataType::string_key_type) {
                        throw exceptions::ParsingException {};
                    }
                case '.':
                    if (last_type == DataType::unknown || last_type == DataType::integer_type) {
                        last_type = DataType::double_type;
                        last_value.push_back(ch);
                        continue;
                    } else if (last_type != DataType::string_type && last_type != DataType::string_key_type) {
                        throw exceptions::ParsingException {};
                    }
                case '\n':
                case '\t':
                case ' ':
                    if (last_type == DataType::unknown) {
                        continue;
                    } else if (last_type != DataType::string_key_type && last_type != DataType::string_type) {
                        throw exceptions::ParsingException {};
                    }
                default:
                    switch (last_type) {
                        case DataType::string_type:
                            last_value.push_back(ch);
                            continue;
                        case DataType::string_key_type:
                            last_key.push_back(ch);
                            continue;
                        case DataType::unknown:
                            if (isdigit(ch)) {
                                last_type = DataType::integer_type;
                                last_value.push_back(ch);
                            }
                            continue;
                        default:
                            if (isdigit(ch)) {
                                last_value.push_back(ch);
                                continue;
                            }
                            throw exceptions::ParsingException {};
                    }
            }
        }
        return std::move(main_object);
    }
}
