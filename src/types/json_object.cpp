#include <stdexcept>
#include "json_object.h"
#include "json.h"
#include "indent.h"

namespace simple_json::types {
    using namespace indent;
    #pragma region Constructors

    JsonObject::JsonObject(json_list_type &initializer_list) : map_type(initializer_list) {}

    JsonObject::JsonObject(json_list_type &&initializer_list) : map_type(initializer_list) {}

    #pragma endregion

    #pragma region Methods

    Json JsonObject::get(const char *key, const Json &default_return) const {
        try {
            return at(JsonKey{key});
        } catch (std::out_of_range &e) {
            return default_return;
        }
    }

    Json JsonObject::get(const char *key, Json && default_return) const {
        try {
            return at(JsonKey{key});
        } catch (std::out_of_range &e) {
            return std::move(default_return);
        }
    }

#pragma endregion

    #pragma region Operator Overloading OStream

    std::ostream & operator<<(std::ostream &os, const JsonObject &json_object) {
        if (indent_length == 0) {
            return json_object.stream_without_indent(os);
        }
        return json_object.stream_with_indent(os, indent_length);
    }

    #pragma endregion

    #pragma region Private Method

    std::ostream & JsonObject::stream_without_indent(std::ostream &os) const {
        os << '{';
        for (const auto &p: *this) {
            os << p.first << ": " << p.second << (p.first == std::prev(end())->first ? "" : ", ");
        }
        os << '}';
        return os;
    }

    std::ostream &JsonObject::stream_with_indent(std::ostream &os, size_t local_indent) const {
        os << '{';
        for (const auto &p: *this) {
            os << std::endl;
            os << std::setw(local_indent) << p.first << ": ";
            switch (p.second.used_type) {
                case DataType::json_object_type:
                    p.second.data_json_object->stream_with_indent(os, local_indent + indent_length);
                    break;
                case DataType::array_type:
                    p.second.data_array->stream_with_indent(os, local_indent + indent_length);
                    break;
                default:
                    os << p.second;
            }
            os << (p.first == std::prev(end())->first ? "" : ",");
        }
        os << '\n' << std::setw(local_indent - indent_length) << '}';
        return os;
    }

    #pragma endregion
}
