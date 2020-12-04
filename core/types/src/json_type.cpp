#include <stdexcept>
#include "json_type.h"
#include "json_item.h"
#include <utility>

#pragma region Constructors

Json::Json() : map_type() {}
Json::Json(Json && json) noexcept : map_type(std::move(json)) {}

#pragma endregion

#pragma region Methods

JsonItem Json::get(const char * key, JsonItem & default_return) {
    try {
        return at(key);
    } catch (std::out_of_range &e) {
        return default_return;
    }
}

JsonItem Json::get(const char * key, JsonItem && default_return) {
    return std::move(get(key, default_return));
}

#pragma endregion
