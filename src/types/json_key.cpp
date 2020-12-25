#include "json_key.h"

namespace simple_json::types {
    #pragma region Constructors

    JsonKey::JsonKey(char * key) : key {new std::string {key}} {}

    JsonKey::JsonKey(std::string & key) : key {new std::string {key}} {}

    JsonKey::JsonKey(std::string && key) : JsonKey(key) {}

    JsonKey::JsonKey(const JsonKey & json_key) : key {new std::string {*json_key.key}} {}

    JsonKey::JsonKey(JsonKey && json_key) noexcept : key {json_key.key} {
        json_key.key = nullptr;
    }

    #pragma endregion

    #pragma region Destructor

    JsonKey::~JsonKey() {
        delete key;
    }

    #pragma endregion

    #pragma region Operator Overloading

    std::ostream & operator<<(std::ostream & os, const JsonKey & json_key) {
        os << '"' << * json_key.key << '"';
        return os;
    }

    std::ostream & operator<<(std::ostream & os, const JsonKey && json_key) {
        os << json_key;
        return os;
    }

    bool JsonKey::operator<(const JsonKey & right_json_key) const {
        return * key < * right_json_key.key;
    }

    bool JsonKey::operator>(const JsonKey & right_json_key) const {
        return * key > * right_json_key.key;
    }

    bool JsonKey::operator==(const JsonKey & right_json_key) const {
        return * key == * right_json_key.key;
    }

    JsonKey operator""_json_key(const char * key_ptr, size_t) {
        return JsonKey(key_ptr);
    }

    #pragma endregion
}
