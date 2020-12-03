#include "base_type.h"
#include "enum_types.h"
#include "base_exception.h"

// Constructors body
#pragma region Constructors
JsonItem::JsonItem(double data) : data_double {data}, used_type {DataType::double_type} {}

JsonItem::JsonItem(int data) : data_int {data}, used_type(DataType::integer_type) {}

JsonItem::JsonItem(float data) : data_float {data}, used_type(DataType::float_type) {}

JsonItem::JsonItem(JsonItem::type_array * data) : data_array(data), used_type(DataType::array_type) {}

JsonItem::JsonItem(JsonItem::type_array && data) : data_array(&data), used_type(DataType::array_type) {}

JsonItem::JsonItem(std::string * data) : data_string {data}, used_type(DataType::string_type) {}

JsonItem::JsonItem(std::string &&data) : data_string {&data}, used_type(DataType::string_type) {}
#pragma endregion

JsonItem::operator int () const {
// operator overloading body
#pragma region Operators overloading
JsonItem::operator int () {
    if (used_type == DataType::integer_type) {
        return data_int;
    }
    throw BadConversion {DataType::integer_type};
}

JsonItem::operator float() {
    if (used_type == DataType::float_type) {
        return data_float;
    }

    throw BadConversion(DataType::unknown, DataType::float_type);
}

JsonItem::operator double () {
    if (used_type == DataType::double_type) {
        return data_double;
    }

    throw BadConversion(DataType::unknown, DataType::double_type);
}

JsonItem::operator std::string () {
    if (used_type == DataType::string_type) {
        return *data_string;
    }

    throw BadConversion(DataType::unknown, DataType::string_type);
}

JsonItem::operator type_array() {
    return JsonItem::type_array();
}
#pragma endregion

// Destructor
JsonItem::~JsonItem() {
    if (used_type == DataType::string_type) {
        delete data_string;
    }
}
