#include "base_type.h"
#include "enum_types.h"
#include "base_exception.h"

JsonItem::JsonItem(double data) : data_double {data}, used_type {DataType::double_type} {}

JsonItem::JsonItem(int data) : data_int {data}, used_type(DataType::integer_type) {}

JsonItem::JsonItem(std::string * data) : data_string {data}, used_type(DataType::string_type) {}

JsonItem::JsonItem(std::string &&data) : data_string {&data}, used_type(DataType::string_type) {}

JsonItem::operator int () const {
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

JsonItem::~JsonItem() {
    if (used_type == DataType::string_type) {
        delete data_string;
    }
}
