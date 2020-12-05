#ifndef SIMPLE_JSON_JSON_TYPE_H
#define SIMPLE_JSON_JSON_TYPE_H

#include <map>
#include <string>
#include <initializer_list>
#include <utility>

class JsonItem;
class Array;
typedef std::map<std::string, JsonItem> map_type;
typedef std::initializer_list<std::pair<const std::string, JsonItem>> json_list_type;

class Json : public map_type {
public:
    JsonItem get(const char *, JsonItem &);
    JsonItem get(const char *, JsonItem &&);
    Json() = default;
    Json(json_list_type &);
    Json(json_list_type &&);
    Json(Json &&) noexcept = default;
    Json(Json &) = default;
};

#endif //SIMPLE_JSON_JSON_TYPE_H
