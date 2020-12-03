#include <enum_types.h>

std::string type_convertor(DataType type) {
    switch (type) {
        case 0:
            return "int";
        case 1:
            return "float";
        case 2:
            return "string";
        case 3:
            return "double";
        default:
            return "";
    }
}
