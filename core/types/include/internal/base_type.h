#ifndef SIMPLE_JSON_BASE_TYPE_H
#define SIMPLE_JSON_BASE_TYPE_H
#include <string>
#include <vector>
#include "enum_types.h"

class JsonItem {
    typedef std::vector<JsonItem> type_array;

private:
    union {
        int data_int;
        double data_double;
        type_array * data_array;
        std::string * data_string;
    };
    DataType used_type;
public:

    // Constructors
    JsonItem(double data);
    JsonItem(int data);
    JsonItem(float data);
    JsonItem(type_array * data);
    JsonItem(type_array && data);
    JsonItem(std::string * data);
    JsonItem(std::string && data);

    // operator overloading for cast
    operator int();
    operator float();
    operator double();
    operator type_array();
    operator std::string();

    // Destructors
    ~JsonItem();
};
#endif
