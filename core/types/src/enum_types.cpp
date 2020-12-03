#include <enum_types.h>

std::string type_convertor(DataType type) {
    switch (type) {
        case DataType::integer_type:
            return "int";
        case DataType::float_type:
            return "float";
        case DataType::string_type:
            return "string";
        case DataType::double_type:
            return "double";
        case DataType::array_type:
            return "vector<BaseType>";
        default:
            return "";
    }
}
