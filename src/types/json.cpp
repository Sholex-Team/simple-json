#include "json.h"
#include "array_type.h"
#include "enum_types.h"
#include "bad_conversion.h"
#include "stream_exceptions.h"
#include "invalid_index.h"
#include <utility>

using namespace simple_json;
using namespace ::types;
using namespace ::exceptions;

// Constructors body
#pragma region Constructors
Json::Json(double data) : data_double {data}, used_type {DataType::double_type} {}

Json::Json(int data) : data_int {data}, used_type {DataType::integer_type} {}

Json::Json(bool data) : data_boolean {data}, used_type {DataType::boolean_type} {}

Json::Json(std::nullptr_t t) : used_type(DataType::null_type) {}

Json::Json(Array data) : data_array {new Array(std::move(data))}, used_type {DataType::array_type} {}

Json::Json(Array && data) : data_array {new Array(std::move(data))}, used_type {DataType::array_type} {}

Json::Json(array_list_type & list_initial) : data_array {new Array{list_initial}}, used_type(DataType::array_type) {}

Json::Json(array_list_type && list_initial) : data_array {new Array{list_initial}}, used_type(DataType::array_type) {}

Json::Json(std::string data) : data_string {new std::string {std::move(data)}}, used_type {DataType::string_type} {}

Json::Json(std::string && data) : data_string {new std::string {std::move(data)}}, used_type {DataType::string_type} {}

Json::Json(const char * data) : data_string {new std::string {data}}, used_type {DataType::string_type} {}

Json::Json(JsonObject data) : data_json_object {new JsonObject {std::move(data)}}, used_type {DataType::json_object_type} {}

Json::Json(JsonObject && data) : data_json_object {new JsonObject {std::move(data)}}, used_type {DataType::json_object_type} {}

Json::Json(json_list_type & initializer_list) : data_json_object {new JsonObject {initializer_list}},
                                                used_type {DataType::json_object_type} {}

Json::Json(json_list_type && initializer_list) : data_json_object {new JsonObject {initializer_list}},
                                                 used_type {DataType::json_object_type} {}

Json::Json(const Json & json_item) : used_type {json_item.used_type} {
    copy(json_item);
}

Json::Json(Json && json_item) noexcept : used_type {json_item.used_type} {
    move(json_item);
}

Json::Json() : used_type {DataType::unknown} {}

#pragma endregion

#pragma region Operator Overloading

Json::operator int() const {
    if (used_type == DataType::integer_type) {
        return data_int;
    }
    throw BadConversion {DataType::integer_type};
}

Json::operator double() const {
    if (used_type == DataType::double_type) {
        return data_double;
    }
    throw BadConversion{DataType::double_type};
}

Json::operator std::string() const {
    if (used_type == DataType::string_type) {
        return * data_string;
    }
    throw BadConversion{DataType::string_type};
}

Json::operator Array() const {
    if (used_type == DataType::array_type) {
        return * data_array;
    }
    throw BadConversion {DataType::array_type};
}

Json::operator JsonObject() const {
    if (used_type == DataType::json_object_type) {
        return * data_json_object;
    }
    throw BadConversion {DataType::json_object_type};
}

Json & Json::operator=(const Json & json_item) {
    used_type = json_item.used_type;
    copy(json_item);
    return *this;
}

Json & Json::operator=(Json && json_item) noexcept {
    used_type = json_item.used_type;
    move(json_item);
    return *this;
}

Json & Json::operator[](const int & index) {
    if (used_type == DataType::array_type) {
        return data_array->at(index);
    }
    throw InvalidIndexException(used_type);
}

Json & Json::operator[](const char * & index) {
    if (used_type == DataType::json_object_type) {
        return data_json_object->at(JsonKey {index});
    }
    throw InvalidIndexException(used_type);
}

bool Json::operator==(const Json & json_item) const {
    if (json_item.used_type != used_type) {
        return false;
    }
    switch (used_type) {
        case DataType::integer_type:
            return data_int == json_item.data_int;
        case DataType::string_type:
            return data_string == json_item.data_string;
        case DataType::double_type:
            return data_double == json_item.data_double;
        case DataType::boolean_type:
            return data_boolean == json_item.data_boolean;
        case DataType::array_type:
            return data_array == json_item.data_array;
        case DataType::json_object_type:
            return data_json_object == json_item.data_json_object;
        default:
            return true;
    }
}

bool Json::operator==(const Json && json_item) const {
    return *this == json_item;
}

#pragma endregion

#pragma region Destructor
Json::~Json() {
    switch (used_type) {
        case DataType::array_type:
            delete data_array;
            return;
        case DataType::json_object_type:
            delete data_json_object;
            return;
        case DataType::string_type:
            delete data_string;
            return;
        default:
            return;
    }
}

#pragma endregion Destructor

#pragma region Private Methods

void Json::move(Json & json_item) noexcept {
    switch (json_item.used_type) {
        case DataType::integer_type:
            data_int = json_item.data_int;
            return;
        case DataType::double_type:
            data_double = json_item.data_double;
            return;
        case DataType::boolean_type:
            data_boolean = json_item.data_boolean;
            return;
        case DataType::string_type:
            data_string = json_item.data_string;
            json_item.data_string = nullptr;
            return;
        case DataType::array_type:
            data_array = json_item.data_array;
            json_item.data_array = nullptr;
            return;
        case DataType::json_object_type:
            data_json_object = json_item.data_json_object;
            json_item.data_json_object = nullptr;
            return;
        default:
            return;
    }
}

void Json::copy(const Json & json_item) {
    switch (json_item.used_type) {
        case DataType::integer_type:
            data_int = json_item.data_int;
            return;
        case DataType::double_type:
            data_double = json_item.data_double;
            return;
        case DataType::boolean_type:
            data_boolean = json_item.data_boolean;
            return;
        case DataType::string_type:
            data_string = new std::string {*json_item.data_string};
            return;
        case DataType::array_type:
            data_array = new Array {*json_item.data_array};
            return;
        case DataType::json_object_type:
            data_json_object = new JsonObject {*json_item.data_json_object};
            return;
        default:
            return;
    }
}

#pragma endregion

#pragma region OS Overloading

std::ostream & types::operator<<(std::ostream & os, const Json & json_item) {
    switch (json_item.used_type) {
        case DataType::integer_type:
            os << json_item.data_int;
            break;
        case DataType::string_type:
            os << '"' << * (json_item.data_string) << '"';
            break;
        case DataType::double_type:
            os << json_item.data_double;
            break;
        case DataType::boolean_type:
            os << json_item.data_boolean;
            break;
        case DataType::array_type:
            os << * json_item.data_array;
            break;
        case DataType::json_object_type:
            os << * json_item.data_json_object;
            break;
        case DataType::null_type:
            os << nullptr;
            break;
        default:
            throw StreamInsertionException();
    }
    return os;
}

std::ostream & types::operator<<(std::ostream & os, const Json && json_item) {
    os << json_item;
    return os;
}

#pragma endregion

#pragma region Public Method

Json & Json::at(const int index) {
    return operator[](index);
}

Json & Json::at(const char * index) {
    return operator[](index);
}

#pragma endregion
