#include <stdexcept>
#include "types/json_object.h"
#include "types/json.h"
#include "indent.h"

namespace simple_json::types {
    #pragma region Constructors

    JsonObject::JsonObject(const json_list_type & initializer_list) : map_type(initializer_list) {}

    #pragma endregion

    #pragma region Methods

    Json JsonObject::get(const JsonKey & key, const Json & default_return) const {
        try {
            return at(key);
        } catch (std::out_of_range &e) {
            return default_return;
        }
    }

    Json JsonObject::get(const JsonKey & key, Json && default_return) const {
        try {
            return at(key);
        } catch (std::out_of_range &e) {
            return std::move(default_return);
        }
    }

    Json JsonObject::get(const std::string & key, Json && default_return) const {
        return get(JsonKey{key}, default_return);
    }

    Json JsonObject::get(const std::string & key, const Json & default_return) const {
        return get(JsonKey{key}, default_return);
    }

    #pragma endregion

    #pragma region Operator Overloading OStream

    std::ostream & operator<<(std::ostream & os, const JsonObject & json_object) {
        if (indent::indent_length == 0) {
            return json_object.stream_without_indent(os);
        }
        return json_object.stream_with_indent(os, indent::indent_length);
    }

    #pragma endregion

    #pragma region Private Method

    std::ostream & JsonObject::stream_without_indent(std::ostream & os) const {
        os << '{';
        for (const auto &p: *this) {
            os << p.first << ": " << ((p.second.type() == DataType::string_type) ? p.second.serialize() : p.second)
            << (p.first == std::prev(end())->first ? "" : ", ");
        }
        os << '}';
        return os;
    }

    std::ostream & JsonObject::stream_with_indent(std::ostream & os, size_t local_indent) const {
        os << '{';
        for (const auto &p: *this) {
            os << std::endl;
            os << std::setw(local_indent + 1) << p.first << ": ";
            switch (p.second.used_type) {
                case DataType::json_object_type:
                    p.second.data_json_object->stream_with_indent(os, local_indent + indent::indent_length);
                    break;
                case DataType::array_type:
                    p.second.data_array->stream_with_indent(os, local_indent + indent::indent_length);
                    break;
                case DataType::string_type:
                    os << p.second.serialize();
                    break;
                default:
                    os << p.second;
            }
            os << (p.first == std::prev(end())->first ? "" : ",");
        }
        os << '\n' << std::setw(local_indent - indent::indent_length + 1) << '}';
        return os;
    }

    #pragma endregion
}
