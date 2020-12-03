#include <stdexcept>
#include "json_type.h"
#pragma region Constructors
Json::Json() : map_type() {}
Json::Json(Json && json) noexcept : map_type(std::move(json)) {}
#pragma endregion
#pragma region Methods
JsonItem Json::get(const std::string& key, const JsonItem& default_return) const {
    try {
        return this->at(key);
    } catch (std::out_of_range e) {
        return default_return;
    }
}
#pragma endregion
