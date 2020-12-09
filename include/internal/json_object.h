#ifndef SIMPLE_JSON_JSON_OBJECT_H
#define SIMPLE_JSON_JSON_OBJECT_H

#include <map>
#include <string>
#include <initializer_list>
#include <utility>
#include "json_key.h"
#include "aliases.h"
#include "iostream"
#include <utility>
#include <iomanip>

namespace simple_json::types {
    class Json;
    class Array;
    typedef std::map<JsonKey, Json> map_type;
    typedef std::initializer_list<std::pair<const JsonKey, Json>> json_list_type;

    class JsonObject : public map_type {
        private:
            std::ostream & stream_without_indent(std::ostream &) const;
            std::ostream & stream_with_indent(std::ostream &, size_t) const;
        public:
            Json get(const char *, const Json &) const;
            Json get(const char *, Json &&) const;
            JsonObject() = default;
            JsonObject(json_list_type &);
            JsonObject(json_list_type &&);
            JsonObject(JsonObject &&) noexcept = default;
            JsonObject(JsonObject &) = default;

            // Friends
            friend std::ostream & operator<<(std::ostream &, const JsonObject &);
            friend Array;
        };

    std::ostream & operator<<(std::ostream &, const JsonObject &);
}

#endif //SIMPLE_JSON_JSON_OBJECT_H
