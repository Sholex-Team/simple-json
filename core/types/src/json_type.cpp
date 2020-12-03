
#include <stdexcept>
#include "json_type.h"

auto Json::get(const std::string& key, const JsonItem& default_return) const {
    try {
        return this->at(key);
    } catch (std::out_of_range e) {
        return default_return;
    }
}

Json::Json(Json && json) { map_type(std::move(json)); }
