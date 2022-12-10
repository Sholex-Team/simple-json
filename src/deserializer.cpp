#include "deserializer.h"

namespace simple_json::deserializer {
    using Json = types::Json;
    using DataType = types::DataType;
    using JsonKey = types::JsonKey;
    using Errors = exceptions::ParsingException::Errors;

    namespace {
        #pragma region Private Methods

        void Deserializer::general_push_or_exception() {
            switch (last_type) {
                case DataType::STRING_TYPE:
                    last_value.push_back(ch);
                    return;
                case DataType::STRING_KEY_TYPE:
                    last_key.push_back(ch);
                    return;
                case DataType::UNKNOWN:
                    if (!primary_stack.empty() && ((primary_stack.top()->type() ==
                    DataType::ARRAY_TYPE && !array_split) || (primary_stack.top()->type() ==
                    DataType::JSON_OBJECT_TYPE && !key_split)))
                        throw exceptions::ParsingException {Errors::invalid_character};
                    last_value.push_back(ch);
                    if (isdigit(ch)) {
                        last_type = DataType::INTEGER_TYPE;
                        return;
                    }
                    if (is_special()) {
                        last_type = DataType::SPECIAL_TYPE;
                        return;
                    }
                    throw exceptions::ParsingException {Errors::invalid_character};
                case DataType::SPECIAL_TYPE:
                    last_value.push_back(ch);
                    if (is_special()) {
                        add_to_top();
                        return;
                    }
                    throw exceptions::ParsingException {Errors::invalid_character};
                default:
                    if (isdigit(ch)) {
                        if (is_spaced)
                            throw exceptions::ParsingException {Errors::illegal_space};
                        last_value.push_back(ch);
                        return;
                    }
                    throw exceptions::ParsingException {Errors::invalid_character};
            }
        }

        bool Deserializer::is_special() {
            return true_str.rfind(last_value, 0) == 0 ||
            false_str.rfind(last_value, 0) == 0 ||
            null_str.rfind(last_value, 0) == 0;
        }

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
            key_split = false;
        }

        void Deserializer::pop_stack() {
            if (array_split) {
                if (primary_stack.top()->empty()) {
                    array_split = false;
                } else {
                    throw exceptions::ParsingException {Errors::illegal_array_split};
                }
            }
            primary_stack.pop();
            if (primary_stack.empty()) {
                finished = true;
            }
        }

        void Deserializer::strings_or_exception() {
            if (!(last_type == DataType::STRING_TYPE || last_type == DataType::STRING_KEY_TYPE)) {
                throw exceptions::ParsingException {Errors::invalid_character};
            }
        }

        void Deserializer::add_to_top() {
            if (primary_stack.top()->type() == DataType::ARRAY_TYPE) {
                switch (last_type) {
                    case DataType::DOUBLE_TYPE:
                        primary_stack.top()->push_back(double_value);
                        break;
                    case DataType::INTEGER_TYPE:
                        primary_stack.top()->push_back(integer_value);
                        break;
                    case DataType::SPECIAL_TYPE:
                        if (last_value == true_str) {
                            primary_stack.top()->push_back(true);
                        } else if (last_value == false_str) {
                            primary_stack.top()->push_back(false);
                        } else if (last_value == null_str) {
                            primary_stack.top()->push_back(nullptr);
                        } else {
                            return;
                        }
                        break;
                    default:
                        primary_stack.top()->push_back(last_value);
                }
                array_split = false;
            } else {
                switch (last_type) {
                    case DataType::DOUBLE_TYPE:
                        primary_stack.top()->insert({JsonKey {last_key}, double_value});
                        break;
                    case DataType::INTEGER_TYPE:
                        primary_stack.top()->insert({JsonKey {last_key}, integer_value});
                        break;
                    case DataType::SPECIAL_TYPE:
                        if (last_value == true_str) {
                            primary_stack.top()->insert({JsonKey {last_key}, true});
                        } else if (last_value == false_str) {
                            primary_stack.top()->insert({JsonKey {last_key}, false});
                        } else if (last_value == null_str) {
                            primary_stack.top()->insert({JsonKey {last_key}, nullptr});
                        } else {
                            return;
                        }
                        break;
                    default:
                        primary_stack.top()->insert({JsonKey {last_key}, last_value});
                }
                last_key.clear();
                key_split = false;
            }
            last_type = DataType::UNKNOWN;
            last_value.clear();
        }

        void Deserializer::string_push_or_exception() {
            switch (last_type) {
                case DataType::STRING_TYPE:
                    last_value.push_back(ch);
                    return;
                case DataType::STRING_KEY_TYPE:
                    last_key.push_back(ch);
                    return;
                default:
                    throw exceptions::ParsingException {Errors::invalid_character};
            }
        }

        #pragma endregion

        #pragma region Public Methods

        Json Deserializer::deserialize(std::istream && stream) {
            return deserialize(stream);
        }

        Json Deserializer::deserialize(std::istream & stream) {
            while (stream.get(ch)) {
                if (finished && (ch != '\n' && ch != '\t' && ch != '\b')) {
                    throw exceptions::ParsingException {Errors::extra_character};
                }
                if ((ch == '}' || ch == ']' || ch == ',') &&
                    (last_type == DataType::INTEGER_TYPE || last_type == DataType::DOUBLE_TYPE)) {
                    if (last_type == DataType::INTEGER_TYPE) {
                        integer_value = strtol(last_value.c_str(), nullptr, 10);
                    } else {
                        double_value = strtod(last_value.c_str(), nullptr);
                    }
                    is_spaced = false;
                    add_to_top();
                }
                switch (ch) {
                    case '}':
                        if (primary_stack.top()->type() == DataType::JSON_OBJECT_TYPE &&
                            last_type == DataType::UNKNOWN) {
                            pop_stack();
                            continue;
                        }
                        strings_or_exception();
                        continue;
                    case ']':
                        if (primary_stack.top()->type() == DataType::ARRAY_TYPE && last_type == DataType::UNKNOWN) {
                            pop_stack();
                            continue;
                        }
                        strings_or_exception();
                        continue;
                    case ',':
                        if (last_type == DataType::UNKNOWN) {
                            if (key_split || array_split) {
                                throw exceptions::ParsingException {Errors::illegal_array_split};
                            }
                            array_split = true;
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    case ':':
                        if (last_type == DataType::UNKNOWN) {
                            if (key_split || array_split)
                                throw exceptions::ParsingException {Errors::illegal_key_split};
                            key_split = true;
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    case '\\':
                        if (last_type == DataType::STRING_KEY_TYPE || last_type == DataType::STRING_TYPE) {
                            escaped = true;
                            continue;
                        }
                        throw exceptions::ParsingException {Errors::illegal_escape};
                    case '{':
                        if (last_type == DataType::UNKNOWN) {
                            if (primary_stack.empty()) {
                                main_object = DataType::JSON_OBJECT_TYPE;
                                set_main_object();
                                continue;
                            }
                            if (primary_stack.top()->type() == DataType::JSON_OBJECT_TYPE) {
                                if (!last_key.empty()) {
                                    primary_stack.top()->insert({
                                        JsonKey{last_key},
                                        Json(DataType::JSON_OBJECT_TYPE)
                                    });
                                    push_json_object_stack();
                                    continue;
                                }
                                throw exceptions::ParsingException {Errors::empty_key};
                            } else if (primary_stack.top()->type() == DataType::ARRAY_TYPE) {
                                primary_stack.top()->push_back(Json(DataType::JSON_OBJECT_TYPE));
                                push_array_stack();
                            }
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    case '[':
                        if (last_type == DataType::UNKNOWN) {
                            if (primary_stack.empty()) {
                                main_object = DataType::ARRAY_TYPE;
                                set_main_object();
                                continue;
                            }
                            if (primary_stack.top()->type() == DataType::JSON_OBJECT_TYPE) {
                                if (!last_key.empty() && key_split) {
                                    primary_stack.top()->insert({
                                        JsonKey{last_key},
                                        Json(DataType::ARRAY_TYPE)
                                    });
                                    push_json_object_stack();
                                    continue;
                                }
                                throw exceptions::ParsingException {Errors::invalid_key};
                            } else if (primary_stack.top()->type() == DataType::ARRAY_TYPE && array_split) {
                                primary_stack.top()->push_back(Json(DataType::ARRAY_TYPE));
                                push_array_stack();
                                continue;
                            } else {
                                throw exceptions::ParsingException {Errors::invalid_array};
                            }
                        }
                        string_push_or_exception();
                        break;
                    case '"':
                        if (escaped) {
                            if (last_type == DataType::STRING_TYPE)
                                last_value.push_back(ch);
                            else
                                last_key.push_back(ch);
                            escaped = false;
                            continue;
                        }
                        switch (last_type) {
                            case DataType::UNKNOWN:
                                // Creating a string as single object
                                if (primary_stack.empty()) {
                                    last_type = DataType::STRING_TYPE;
                                    continue;
                                }
                                if (primary_stack.top()->type() == DataType::JSON_OBJECT_TYPE) {
                                    // Creating a string as value
                                    if (!last_key.empty() && key_split) {
                                        key_split = false;
                                        last_type = DataType::STRING_TYPE;
                                        continue;
                                        // Creating a string as key
                                    } else if (last_key.empty() && array_split) {
                                        array_split = false;
                                        last_type = DataType::STRING_KEY_TYPE;
                                        continue;
                                    }
                                } else if (primary_stack.top()->type() == DataType::ARRAY_TYPE && array_split) {
                                    // Creating  a string as array value
                                    if (last_key.empty()) {
                                        array_split = false;
                                        last_type = DataType::STRING_TYPE;
                                        continue;
                                    }
                                }
                                throw exceptions::ParsingException {Errors::invalid_string};
                            case DataType::STRING_TYPE:
                                add_to_top();
                                continue;
                            case DataType::STRING_KEY_TYPE:
                                // Closing string key
                                if (!last_key.empty()) {
                                    last_type = DataType::UNKNOWN;
                                    continue;
                                }
                                throw exceptions::ParsingException {Errors::empty_key};
                            default:
                                throw exceptions::ParsingException {Errors::invalid_string};
                        }
                    case '-':
                        if (last_type == DataType::UNKNOWN) {
                            last_type = DataType::INTEGER_TYPE;
                            last_value.push_back(ch);
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    case '.':
                        if (last_type == DataType::UNKNOWN || last_type == DataType::INTEGER_TYPE) {
                            last_type = DataType::DOUBLE_TYPE;
                            last_value.push_back(ch);
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    case '\b':
                    case '\t':
                    case '\n':
                        if (last_type == DataType::STRING_KEY_TYPE || last_type == DataType::STRING_TYPE)
                            throw exceptions::ParsingException {Errors::illegal_escape_sequences};
                        if (last_type != DataType::UNKNOWN) {
                            is_spaced = true;
                        }
                        continue;
                    case 'n':
                        if (escaped) {
                            escaped = false;
                            ch = '\n';
                        }
                        general_push_or_exception();
                        continue;
                    case 't':
                        if (escaped) {
                            escaped = false;
                            ch = '\t';
                        }
                        general_push_or_exception();
                        continue;
                    case 'b':
                        if (escaped) {
                            escaped = false;
                            ch = '\b';
                        }
                        string_push_or_exception();
                        continue;
                    case ' ':
                        if (last_type == DataType::UNKNOWN)
                            continue;
                        else if (last_type == DataType::DOUBLE_TYPE || last_type == DataType::INTEGER_TYPE) {
                            is_spaced = true;
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    default:
                        general_push_or_exception();
                }
            }
            if (main_object.type() == DataType::UNKNOWN &&
                (last_type == DataType::INTEGER_TYPE || last_type == DataType::DOUBLE_TYPE)) {
                if (last_type == DataType::INTEGER_TYPE)
                    main_object = strtol(last_value.c_str(), nullptr, 10);
                else
                    main_object = strtod(last_value.c_str(), nullptr);
                finished = true;
            }
            if (!finished)
                throw exceptions::ParsingException {Errors::unfinished_json};
            return std::move(main_object);
        }

        #pragma endregion

        Load::~Load() {
            if (file_stream.is_open())
                file_stream.close();
        }

        Load::Load(const std::string & file_path) : file_stream {file_path} {
            if (!file_stream)
                throw exceptions::ReadingFromFileException {};
        }

        simple_json::types::Json simple_json::deserializer::Load::load() {
            return Deserializer {}.deserialize(file_stream);
        }
    }

    simple_json::types::Json loads(const std::string & json_text) {
        return Deserializer {}.deserialize(std::stringstream {json_text});
    }

    simple_json::types::Json load(const std::string & file_path) {
        return Load {file_path}.load();
    }

    simple_json::types::Json load(std::ifstream & fs) {
        if (!fs)
            throw exceptions::ReadingFromFileException {};
        return Deserializer {}.deserialize(fs);
    }
}
