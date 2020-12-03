#include "base_type.h"
#include "enum_types.h"
#include "base_exception.h"

JsonItem::JsonItem(double data) : data_double {data} {}

JsonItem::JsonItem(int data) : data_int {data} {}

JsonItem::JsonItem(float data) : data_float {data} {}

JsonItem::JsonItem(short data) : data_short {data} {}

JsonItem::JsonItem(unsigned short data) : data_u_s {data} {}

JsonItem::JsonItem(unsigned int data) : data_u_i {data} {}

JsonItem::JsonItem(std::string data) : data_string {std::move(data)} {}

JsonItem::JsonItem(std::string &&data) : data_string {std::move(data)} {}

JsonItem::operator int () {
    if (used_type == DataType {0}) {
        return data_int;
    }
    throw BadConversion(DataType {100}, DataType {0});
}