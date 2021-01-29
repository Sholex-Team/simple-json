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
                case DataType::string_type:
                    last_value.push_back(ch);
                    return;
                case DataType::string_key_type:
                    last_key.push_back(ch);
                    return;
                case DataType::unknown:
                    if (!primary_stack.empty() && (
                            (primary_stack.top()->type() == DataType::array_type && !array_split) ||
                            (primary_stack.top()->type() == DataType::json_object_type && !key_split)
                    )) {
                        throw exceptions::ParsingException {Errors::invalid_character};
                    }
                    last_value.push_back(ch);
                    if (isdigit(ch)) {
                        last_type = DataType::integer_type;
                        return;
                    }
                    if (is_special()) {
                        last_type = DataType::special_type;
                        return;
                    }
                    throw exceptions::ParsingException {Errors::invalid_character};
                case DataType::special_type:
                    last_value.push_back(ch);
                    if (is_special()) {
                        add_to_top();
                        return;
                    }
                    throw exceptions::ParsingException {Errors::invalid_character};
                default:
                    if (isdigit(ch)) {
                        if (is_spaced) {
                            throw exceptions::ParsingException {Errors::illegal_space};
                        }
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
            if (!(last_type == DataType::string_type || last_type == DataType::string_key_type)) {
                throw exceptions::ParsingException {Errors::invalid_character};
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
                    case DataType::double_type:
                        primary_stack.top()->insert({JsonKey {last_key}, double_value});
                        break;
                    case DataType::integer_type:
                        primary_stack.top()->insert({JsonKey {last_key}, integer_value});
                        break;
                    case DataType::special_type:
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
                    throw exceptions::ParsingException {Errors::invalid_character};
            }
        }

        #pragma endregion

        #pragma region Public Methods

        Json Deserializer::deserialize(std::istream && stream) {
            return deserialize(stream);
        }

        Json Deserializer::deserialize(std::istream & stream) {
            main_object = DataType::unknown;
            while (stream.get(ch)) {
                if (finished && (ch != '\n' && ch != '\t' && ch != '\b')) {
                    throw exceptions::ParsingException {Errors::extra_character};
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
                        continue;
                    case ']':
                        if (primary_stack.top()->type() == DataType::array_type && last_type == DataType::unknown) {
                            pop_stack();
                            continue;
                        }
                        strings_or_exception();
                        continue;
                    case ',':
                        if (last_type == DataType::unknown) {
                            if (key_split || array_split) {
                                throw exceptions::ParsingException {Errors::illegal_array_split};
                            }
                            array_split = true;
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    case ':':
                        if (last_type == DataType::unknown) {
                            if (key_split || array_split) {
                                throw exceptions::ParsingException {Errors::illegal_key_split};
                            }
                            key_split = true;
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    case '\\':
                        if (last_type == DataType::string_key_type || last_type == DataType::string_type) {
                            escaped = true;
                            continue;
                        }
                        throw exceptions::ParsingException {Errors::illegal_escape};
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
                                throw exceptions::ParsingException {Errors::empty_key};
                            } else if (primary_stack.top()->type() == DataType::array_type) {
                                primary_stack.top()->push_back(Json(DataType::json_object_type));
                                push_array_stack();
                            }
                            continue;
                        }
                        string_push_or_exception();
                        continue;
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
                                    continue;
                                }
                                throw exceptions::ParsingException {Errors::invalid_key};
                            } else if (primary_stack.top()->type() == DataType::array_type && array_split) {
                                primary_stack.top()->push_back(Json(DataType::array_type));
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
                                } else if (primary_stack.top()->type() == DataType::array_type && array_split) {
                                    // Creating  a string as array value
                                    if (last_key.empty()) {
                                        array_split = false;
                                        last_type = DataType::string_type;
                                        continue;
                                    }
                                }
                                throw exceptions::ParsingException {Errors::invalid_string};
                            case DataType::string_type:
                                add_to_top();
                                continue;
                            case DataType::string_key_type:
                                // Closing string key
                                if (!last_key.empty()) {
                                    last_type = DataType::unknown;
                                    continue;
                                }
                                throw exceptions::ParsingException {Errors::empty_key};
                            default:
                                throw exceptions::ParsingException {Errors::invalid_string};
                        }
                    case '-':
                        if (last_type == DataType::unknown) {
                            last_type = DataType::integer_type;
                            last_value.push_back(ch);
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    case '.':
                        if (last_type == DataType::unknown || last_type == DataType::integer_type) {
                            last_type = DataType::double_type;
                            last_value.push_back(ch);
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    case '\b':
                    case '\t':
                    case '\n':
                        if (last_type == DataType::string_key_type || last_type == DataType::string_type) {
                            throw exceptions::ParsingException {Errors::illegal_escape_sequences};
                        }
                        is_spaced = true;
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
                        if (last_type == DataType::unknown) {
                            continue;
                        } else if (last_type == DataType::double_type || last_type == DataType::integer_type) {
                            is_spaced = true;
                            continue;
                        }
                        string_push_or_exception();
                        continue;
                    default:
                        general_push_or_exception();
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
                throw exceptions::ParsingException {Errors::unfinished_json};
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
            return Deserializer {}.deserialize(file_stream);
        }
    }

    /**
     * deserialize as text json
     * @param json_text JSON serialized text
     * @return Json deserialized object
     */
    simple_json::types::Json loads(const std::string & json_text) {
        return Deserializer {}.deserialize(std::stringstream {json_text});
    }

    simple_json::types::Json load(const std::string & file_path) {
        return Load {file_path}.load();
    }

    simple_json::types::Json load(std::ifstream & fs) {
        if (!fs) {
            throw exceptions::ReadingFromFileException {};
        }
        return Deserializer {}.deserialize(fs);
    }
}
