#include <stdexcept>
#include "json_type.h"
#include "json_item.h"
#include <utility>

#pragma region Constructors

JsonObject::JsonObject(json_list_type & initializer_list) : map_type(initializer_list) {}

JsonObject::JsonObject(json_list_type && initializer_list) : map_type(initializer_list) {}

#pragma endregion

#pragma region Methods

Json JsonObject::get(const char * key, Json & default_return) {
    try {
        return at(key);
    } catch (std::out_of_range &e) {
        return default_return;
    }
}

Json JsonObject::get(const char * key, Json && default_return) {
    return std::move(get(key, default_return));
}

#pragma endregion
