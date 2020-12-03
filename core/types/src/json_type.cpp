#include <stdexcept>
#include "json_type.h"
#include "json_item.h"
#pragma region Constructors
Json::Json() : map_type() {}
Json::Json(Json && json) noexcept : map_type(std::move(json)) {}
#pragma endregion
#pragma region Methods
JsonItem Json::get(key_type & key, JsonItem& default_return) {
    try {
        return this->at(key);
    } catch (std::out_of_range e) {
        return default_return;
    }
}
#pragma endregion
