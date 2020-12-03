#include "json_item.h"
#include "enum_types.h"
#include "base_exception.h"
#include <utility>

// Constructors body
#pragma region Constructors
JsonItem::JsonItem(double data) : data_double {data}, used_type {DataType::double_type} {}

JsonItem::JsonItem(int data) : data_int {data}, used_type(DataType::integer_type) {}

JsonItem::JsonItem(JsonItem::type_array data) : data_array {new type_array {std::move(data)}},
used_type(DataType::array_type) {}

JsonItem::JsonItem(JsonItem::type_array && data) : data_array {new type_array {std::move(data)}},
used_type(DataType::array_type) {}

JsonItem::JsonItem(std::string data) : data_string {new std::string {std::move(data)}},
used_type(DataType::string_type) {}

JsonItem::JsonItem(std::string &&data) : data_string {new std::string {std::move(data)}},
used_type(DataType::string_type) {}

JsonItem::JsonItem(Json data) : data_json {new Json {std::move(data)}}, used_type {DataType::json_type} {}

JsonItem::JsonItem(Json &&data) : data_json {new Json {std::move(data)}}, used_type {DataType::json_type} {}

JsonItem::JsonItem(const JsonItem &json_item) {
    used_type = json_item.used_type;
    switch (json_item.used_type) {
        case DataType::integer_type:
            data_int = json_item.data_int;
            return;
        case DataType::double_type:
            data_double = json_item.data_double;
            return;
        case DataType::string_type:
            data_string = new std::string {*json_item.data_string};
            return;
        case DataType::array_type:
            data_array = new type_array {*json_item.data_array};
            return;
        case DataType::json_type:
            data_json = new Json {*json_item.data_json};
            return;
        default:
            return;
    }
}

JsonItem::JsonItem(JsonItem &&json_item) noexcept {
    used_type = json_item.used_type;
    switch (json_item.used_type) {
        case DataType::integer_type:
            data_int = json_item.data_int;
            return;
        case DataType::double_type:
            data_double = json_item.data_double;
            return;
        case DataType::string_type:
            data_string = json_item.data_string;
            json_item.data_string = nullptr;
            return;
        case DataType::array_type:
            data_array = json_item.data_array;
            json_item.data_array = nullptr;
            return;
        case DataType::json_type:
            data_json = json_item.data_json;
            json_item.data_json = nullptr;
            return;
        default:
            return;
    }
}
#pragma endregion

// operator overloading body
#pragma region Operators overloading
JsonItem::operator int () const {
    if (used_type == DataType::integer_type) {
        return data_int;
    }
    throw BadConversion {DataType::integer_type};
}

JsonItem::operator double () const {
    if (used_type == DataType::double_type) {
        return data_double;
    }
    throw BadConversion{DataType::double_type};
}

JsonItem::operator std::string () const {
    if (used_type == DataType::string_type) {
        return * data_string;
    }
    throw BadConversion{DataType::string_type};
}

JsonItem::operator type_array () const {
    if (used_type == DataType::array_type) {
        return * data_array;
    }
    throw BadConversion {DataType::array_type};
}
#pragma endregion

// Destructor
JsonItem::~JsonItem() {
    switch (used_type) {
        case DataType::array_type:
            delete data_array;
            return;
        case DataType::json_type:
            delete data_json;
            return;
        case DataType::string_type:
            delete data_string;
            return;
        default:
            return;
    }
}
