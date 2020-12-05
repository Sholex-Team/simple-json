#include <stdexcept>
#include "json_object.h"
#include "json.h"
#include <utility>

#pragma region Constructors

JsonObject::JsonObject(json_list_type & initializer_list) : map_type(initializer_list) {}

JsonObject::JsonObject(json_list_type && initializer_list) : map_type(initializer_list) {}

#pragma endregion

#pragma region Methods

Json JsonObject::get(JsonKey key, Json & default_return) {
    try {
        return at(JsonKey {key});
    } catch (std::out_of_range &e) {
        return default_return;
    }
}

Json JsonObject::get(JsonKey key, Json && default_return) {
    return std::move(get(key, default_return));
}

#pragma endregion
