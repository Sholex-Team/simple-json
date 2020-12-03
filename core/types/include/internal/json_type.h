#ifndef SIMPLE_JSON_JSON_TYPE_H
#define SIMPLE_JSON_JSON_TYPE_H

#include <map>
#include <string>
#include "json_item.h"

class JsonItem;

typedef std::map<std::string, JsonItem> map_type;

class Json : public map_type {
public:
    auto get(const std::string& key, const JsonItem& default_return) const;

    Json(Json && json);


};

#endif //SIMPLE_JSON_JSON_TYPE_H
