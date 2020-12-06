#include <stdexcept>
#include "json_object.h"
#include "json.h"
#include "indent.h"
#include <utility>

using namespace simple_json;
using namespace ::types;
using namespace simple_json::indent;

#pragma region Constructors

JsonObject::JsonObject(json_list_type & initializer_list) : map_type(initializer_list) {}

JsonObject::JsonObject(json_list_type && initializer_list) : map_type(initializer_list) {}

#pragma endregion

#pragma region Methods

Json JsonObject::get(const char * key, Json & default_return) {
    try {
        return at(JsonKey {key});
    } catch (std::out_of_range &e) {
        return default_return;
    }
}

Json JsonObject::get(const char * key, Json && default_return) {
    return std::move(get(key, default_return));
}

#pragma endregion

#pragma region Operator Overloading OStream


std::ostream & types::operator<<(std::ostream & os, const JsonObject & json_object) {
    if (indent_length == 0) {
        return json_object.create_ostream_without_indent(os);
    }
    return json_object.create_ostream_with_indent(os);
}

std::ostream & types::operator<<(std::ostream & os, const JsonObject && json_object) {
    os << json_object;
    return os;
}

#pragma endregion

#pragma region Private Method

std::ostream & JsonObject::create_ostream_without_indent(std::ostream & os) const {
//    os << '{';
    os << "unset indent";
//    for (const auto & p: * this) {
//        os << p.first << ':' << p.second;
//    }
//    os << '}';
    return os;
}

std::ostream & JsonObject::create_ostream_with_indent(std::ostream & os) const {
//    os << '{';
//    for (const auto & p: * this) {
//        os << p.first << ':' << p.second;
//    }
//    os << '}';
    os << "set indent";
    return os;
}

#pragma endregion
