#ifndef SIMPLE_JSON_JSON_TYPE_H
#define SIMPLE_JSON_JSON_TYPE_H

#include <map>
#include <string>
#include <initializer_list>
#include <utility>

class Json;
class Array;
typedef std::map<std::string, Json> map_type;
typedef std::initializer_list<std::pair<const std::string, Json>> json_list_type;

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

#endif //SIMPLE_JSON_JSON_TYPE_H
