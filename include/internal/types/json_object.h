#ifndef SIMPLE_JSON_JSON_OBJECT_H
#define SIMPLE_JSON_JSON_OBJECT_H

#include <map>
#include <string>
#include <initializer_list>
#include <utility>
#include "json_key.h"
#include "iostream"
#include <utility>
#include <iomanip>

namespace simple_json::types {
    class Json;
    class Array;
    using map_type = std::map<JsonKey, Json>;
    using pair_type = std::pair<const JsonKey, Json>;
    using json_list_type = std::initializer_list<pair_type>;

    class JsonObject : public map_type {
        private:
            std::ostream & stream_without_indent(std::ostream & os) const;
            std::ostream & stream_with_indent(std::ostream & os, size_t local_indent) const;
        public:
            // Constructors
            JsonObject() = default;
            JsonObject(const json_list_type & initializer_list);
            JsonObject(JsonObject && json_object) noexcept = default;
            JsonObject(JsonObject & json_object) = default;

            // Friends
            friend std::ostream & operator<<(std::ostream & os, const JsonObject & json_object);
            friend Array;

            // Public Methods
            Json get(const std::string & key, const Json & default_return) const;
            Json get(const std::string & key, Json && default_return) const;
        };

    std::ostream & operator<<(std::ostream & os, const JsonObject & json_object);
}

#endif //SIMPLE_JSON_JSON_OBJECT_H
