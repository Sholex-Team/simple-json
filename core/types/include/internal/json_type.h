#ifndef SIMPLE_JSON_JSON_TYPE_H
#define SIMPLE_JSON_JSON_TYPE_H

#include <map>
#include <string>
#include "json_item.h"

class JsonItem;

typedef std::map<std::string, JsonItem> map_type;

class Json : public map_type {
public:
    JsonItem get(const std::string& key, const JsonItem& default_return) const;
    Json();
    Json(Json && json) noexcept;
    Json(Json & json) = default;
};

#endif //SIMPLE_JSON_JSON_TYPE_H
