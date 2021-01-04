#include "deserializer.h"

namespace simple_json::deserializer {
    using Json = types::Json;
    using DataType = types::DataType;
    using JsonKey = types::JsonKey;

    namespace {
        #pragma region Private Methods

        void Deserializer::set_main_object() {
            primary_stack.push(&main_object);
            array_split = true;
        }

        void Deserializer::push_array_stack() {
            primary_stack.push(&primary_stack.top()->back());
            array_split = true;
        }

        void Deserializer::push_json_object_stack() {
            primary_stack.push(&primary_stack.top()->at(last_key));
            last_key.clear();
            array_split = true;
        }

        void Deserializer::pop_stack() {
            if (array_split) {
                if (primary_stack.top()->empty()) {
                    array_split = false;
                } else {
                    throw exceptions::ParsingException {};
                }
            }
            primary_stack.pop();
            if (primary_stack.empty()) {
                finished = true;
            }
        }

        void Deserializer::strings_or_exception() {
            if (!(last_type == DataType::string_type || last_type == DataType::string_key_type)) {
                throw exceptions::ParsingException {};
            }
        }

        void Deserializer::add_to_top() {
            if (primary_stack.top()->type() == DataType::array_type) {
                switch (last_type) {
                    case DataType::double_type:
                        primary_stack.top()->push_back(double_value);
                        break;
                    case DataType::integer_type:
                        primary_stack.top()->push_back(integer_value);
                        break;
                    case DataType::special_type:
                        if (last_value == true_str) {
                            primary_stack.top()->push_back(true);
                        } else if (last_value == false_str) {
                            primary_stack.top()->push_back(false);
                        } else if (last_value == null_str) {
                            primary_stack.top()->push_back(nullptr);
                        }
                        break;
                    default:
                        primary_stack.top()->push_back(last_value);
                }
                array_split = false;
            } else {
                switch (last_type) {
                    case DataType::double_type:
                        primary_stack.top()->insert({JsonKey{last_key}, double_value});
                        break;
                    case DataType::integer_type:
                        primary_stack.top()->insert({JsonKey{last_key}, integer_value});
                        break;
                    case DataType::special_type:
                        if (last_value == true_str) {
                            primary_stack.top()->insert({JsonKey{last_key}, true});
                        } else if (last_value == false_str) {
                            primary_stack.top()->insert({JsonKey{last_key}, false});
                        } else if (last_value == null_str) {
                            primary_stack.top()->insert({JsonKey{last_key}, nullptr});
                        }
                        break;
                    default:
                        primary_stack.top()->insert({JsonKey{last_key}, last_value});
                }
                last_key.clear();
                key_split = false;
            }
            last_type = DataType::unknown;
            last_value.clear();
        }

        void Deserializer::string_push_or_exception() {
            switch (last_type) {
                case DataType::string_type:
                    last_value.push_back(ch);
                    return;
                case DataType::string_key_type:
                    last_key.push_back(ch);
                    return;
                default:
                    throw exceptions::ParsingException {};
            }
        }

        #pragma endregion

        #pragma region Public Methods

        Json Deserializer::deserializer(std::istream && stream) {
            return deserializer(stream);
        }

        Json Deserializer::deserializer(std::istream & stream) {
            while (stream.get(ch)) {
                if (finished) {
                    throw exceptions::ParsingException {};
                }
                if ((ch == '}' || ch == ']' || ch == ',') &&
                    (last_type == DataType::integer_type || last_type == DataType::double_type)) {
                    if (last_type == DataType::integer_type) {
                        integer_value = strtol(last_value.c_str(), nullptr, 10);
                    } else {
                        double_value = strtod(last_value.c_str(), nullptr);
                    }
                    add_to_top();
                }
                switch (ch) {
                    case '}':
                        if (primary_stack.top()->type() == DataType::json_object_type &&
                            last_type == DataType::unknown) {
                            pop_stack();
                            continue;
                        }
                        strings_or_exception();
                    case ']':
                        if (primary_stack.top()->type() == DataType::array_type && last_type == DataType::unknown) {
                            pop_stack();
                            continue;
                        }
                        strings_or_exception();
                    case ',':
                        if (last_type == DataType::unknown) {
                            if (key_split || array_split) {
                                throw exceptions::ParsingException {};
                            }
                            array_split = true;
                            continue;
                        } else {
                            string_push_or_exception();
                        }
                    case ':':
                        if (last_type == DataType::unknown) {
                            if (key_split || array_split) {
                                throw exceptions::ParsingException {};
                            }
                            key_split = true;
                            continue;
                        } else {
                            string_push_or_exception();
                        }
                    case '\\':
                        if (last_type == DataType::string_key_type || last_type == DataType::string_type) {
                            escaped = true;
                            continue;
                        }
                        throw exceptions::ParsingException {};
                    case '{':
                        if (last_type == DataType::unknown) {
                            if (primary_stack.empty()) {
                                main_object = DataType::json_object_type;
                                set_main_object();
                                continue;
                            }
                            if (primary_stack.top()->type() == DataType::json_object_type) {
                                if (!last_key.empty()) {
                                    primary_stack.top()->insert({
                                        JsonKey{last_key},
                                        Json(DataType::json_object_type)
                                    });
                                    push_json_object_stack();
                                    continue;
                                }
                                throw exceptions::ParsingException {};
                            } else if (primary_stack.top()->type() == DataType::array_type) {
                                primary_stack.top()->push_back(Json(DataType::json_object_type));
                                push_array_stack();
                            }
                            continue;
                        }
                        string_push_or_exception();
                        break;
                    case '[':
                        if (last_type == DataType::unknown) {
                            if (primary_stack.empty()) {
                                main_object = DataType::array_type;
                                set_main_object();
                                continue;
                            }
                            if (primary_stack.top()->type() == DataType::json_object_type) {
                                if (!last_key.empty() && key_split) {
                                    primary_stack.top()->insert({
                                        JsonKey{last_key},
                                        Json(DataType::array_type)
                                    });
                                    push_json_object_stack();
                                }
                                throw exceptions::ParsingException{};
                            } else if (primary_stack.top()->type() == DataType::array_type && array_split) {
                                primary_stack.top()->push_back(Json(DataType::array_type));
                                push_array_stack();
                            } else {
                                throw exceptions::ParsingException{};
                            }
                        }
                        string_push_or_exception();
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
                                // Creating a string as single object
                                if (primary_stack.empty()) {
                                    last_type = DataType::string_type;
                                    continue;
                                }
                                if (primary_stack.top()->type() == DataType::json_object_type) {
                                    // Creating a string as value
                                    if (!last_key.empty() && key_split) {
                                        key_split = false;
                                        last_type = DataType::string_type;
                                        continue;
                                        // Creating a string as key
                                    } else if (last_key.empty() && array_split) {
                                        array_split = false;
                                        last_type = DataType::string_key_type;
                                        continue;
                                    }
                                } else if (primary_stack.top()->type() == DataType::array_type) {
                                    // Creating  a string as array value
                                    if (last_key.empty() && array_split) {
                                        array_split = false;
                                        last_type = DataType::string_type;
                                        continue;
                                    }
                                }
                                throw exceptions::ParsingException {};
                            case DataType::string_type:
                                // Closing a single item string
                                if (primary_stack.empty()) {
                                    finished = true;
                                    main_object = Json {last_value};
                                }
                                // Closing a json object string value
                                if (primary_stack.top()->type() == DataType::json_object_type) {
                                    primary_stack.top()->insert({
                                                                        JsonKey{last_key},
                                                                        Json(last_value)
                                                                });
                                    last_value.clear();
                                    last_key.clear();
                                    last_type = DataType::unknown;
                                    continue;
                                    // Closing an array string value
                                } else if (primary_stack.top()->type() == DataType::array_type) {
                                    primary_stack.top()->push_back(Json(last_value));
                                    last_value.clear();
                                    last_type = DataType::unknown;
                                    continue;
                                }
                                throw exceptions::ParsingException {};
                            case DataType::string_key_type:
                                // Closing string key
                                if (!last_key.empty()) {
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
                                if ((primary_stack.top()->type() == DataType::array_type && !array_split) ||
                                    (primary_stack.top()->type() == DataType::json_object_type && !key_split)) {
                                    throw exceptions::ParsingException {};
                                }
                                if (isdigit(ch)) {
                                    last_type = DataType::integer_type;
                                    last_value.push_back(ch);
                                    continue;
                                }
                                throw exceptions::ParsingException {};
                            case DataType::special_type:
                                last_value.push_back(ch);
                                if (last_value.rfind(true_str, 0) == 0 ||
                                    last_value.rfind(false_str, 0) == 0 ||
                                    last_value.rfind(null_str, 0)) {
                                    if (last_value == true_str) {
                                        if (primary_stack.empty()) {
                                            finished = true;
                                            main_object = Json(true);
                                            continue;
                                        }
                                        if (primary_stack.top()->type() == DataType::array_type) {
                                            primary_stack.top()->push_back(Json(true));
                                            array_split = false;
                                            last_type = DataType::unknown;
                                            continue;
                                        } else if (primary_stack.top()->type() == DataType::json_object_type) {
                                            primary_stack.top()->insert({
                                                                                JsonKey{last_key},
                                                                                Json(true)
                                                                        });
                                            last_value.clear();
                                            last_key.clear();
                                            last_type = DataType::unknown;
                                            continue;
                                        }
                                    } else if (last_value == false_str) {
                                        if (primary_stack.empty()) {
                                            finished = true;
                                            main_object = Json(false);
                                            continue;
                                        }
                                        if (primary_stack.top()->type() == DataType::array_type) {
                                            primary_stack.top()->push_back(Json(false));
                                            array_split = false;
                                            last_type = DataType::unknown;
                                            continue;
                                        } else if (primary_stack.top()->type() == DataType::json_object_type) {
                                            primary_stack.top()->insert({
                                                                                JsonKey{last_key},
                                                                                Json(false)
                                                                        });
                                            last_value.clear();
                                            last_key.clear();
                                            last_type = DataType::unknown;
                                            continue;
                                        }
                                    }
                                }
                            default:
                                if (isdigit(ch)) {
                                    last_value.push_back(ch);
                                    continue;
                                }
                                throw exceptions::ParsingException {};
                        }
                }
            }
            if (main_object.type() == DataType::unknown &&
                (last_type == DataType::integer_type || last_type == DataType::double_type)) {
                if (last_type == DataType::integer_type) {
                    main_object = strtol(last_value.c_str(), nullptr, 10);
                } else {
                    main_object = strtod(last_value.c_str(), nullptr);
                }
                finished = true;
            }
            if (!finished) {
                throw exceptions::ParsingException {};
            }
            return std::move(main_object);
        }

        #pragma endregion

        Load::~Load() {
            if (file_stream.is_open()) {
                file_stream.close();
            }
        }

        Load::Load(const std::string & file_path) : file_stream {file_path} {
            if (!file_stream) {
                throw exceptions::ReadingFromFileException {};
            }
        }

        simple_json::types::Json simple_json::deserializer::Load::load() {
            return deserializer(file_stream);
        }
    }

    simple_json::types::Json loads(const std::string & json_text) {
        return deserializer(std::stringstream {json_text});
    }

    simple_json::types::Json load(const std::string & file_path) {
        return Load {file_path}.load();
    }

    simple_json::types::Json load(std::ifstream & file_stream) {
        if (!file_stream) {
            throw exceptions::ReadingFromFileException {};
        }
        return deserializer(file_stream);
    }
}
