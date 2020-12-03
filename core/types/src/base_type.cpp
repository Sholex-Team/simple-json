#include "base_type.h"
#include "enum_types.h"
#include "base_exception.h"

JsonItem::JsonItem(double data) : data_double {data}, used_type {DataType::double_type} {}

JsonItem::JsonItem(int data) : data_int {data}, used_type(DataType::integer_type) {}

JsonItem::JsonItem(float data) : data_float {data}, used_type(DataType::float_type) {}

JsonItem::JsonItem(std::string * data) : data_string {data}, used_type(DataType::string_type) {}

JsonItem::JsonItem(std::string &&data) : data_string {&data}, used_type(DataType::string_type) {}

JsonItem::operator int () {
    if (used_type == DataType {0}) {
        return data_int;
    }
    throw BadConversion(DataType {100}, DataType {0});
}