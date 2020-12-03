#ifndef SIMPLE_JSON_JSON_TYPE_H
#define SIMPLE_JSON_JSON_TYPE_H

#include <map>
#include <string>

class JsonItem;

typedef std::map<std::string, JsonItem> map_type;

class Json : public map_type {
public:
    JsonItem get(key_type& key, JsonItem& default_return);
    Json();
    Json(Json && json) noexcept;
    Json(Json & json) = default;
};

#endif //SIMPLE_JSON_JSON_TYPE_H
