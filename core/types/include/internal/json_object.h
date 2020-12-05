#ifndef SIMPLE_JSON_JSON_OBJECT_H
#define SIMPLE_JSON_JSON_OBJECT_H

#include <map>
#include <string>
#include <initializer_list>
#include <utility>
#include "json_key.h"

class Json;
class Array;
typedef std::map<JsonKey, Json> map_type;
typedef std::initializer_list<std::pair<const JsonKey, Json>> json_list_type;

class JsonObject : public map_type {
public:
    Json get(const char *, Json &);
    Json get(const char *, Json &&);
    JsonObject() = default;
    JsonObject(json_list_type &);
    JsonObject(json_list_type &&);
    JsonObject(JsonObject &&) noexcept = default;
    JsonObject(JsonObject &) = default;
};

#endif //SIMPLE_JSON_JSON_OBJECT_H
