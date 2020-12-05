#include "json_key.h"

#pragma region Constructors

JsonKey::JsonKey(char * key) : key {new std::string {key}} {}

JsonKey::JsonKey(std::string & key) : key {new std::string {key}} {}

JsonKey::JsonKey(std::string && key) : JsonKey(key) {}

JsonKey::JsonKey(JsonKey & json_key) : key {new std::string {*json_key.key}} {}

JsonKey::JsonKey(JsonKey && json_key) noexcept : key {json_key.key} {
    json_key.key = nullptr;
}

#pragma endregion

#pragma Destructor

JsonKey::~JsonKey() {
    delete key;
}

#pragma endregion

#pragma region Operator Overloading

bool JsonKey::operator<(const JsonKey & json_key) {
    return key < json_key.key;
}

bool JsonKey::operator>(const JsonKey & json_key) {
    return key > json_key.key;
}

bool JsonKey::operator==(const JsonKey & json_key) {
    return key == json_key.key;
}

JsonKey operator""_json_key(const char * key_ptr, size_t) {
    return JsonKey(key_ptr);
}

#pragma endregion