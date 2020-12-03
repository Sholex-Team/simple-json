#ifndef SIMPLE_JSON_BASE_TYPE_H
#define SIMPLE_JSON_BASE_TYPE_H
#include <string>
#include "enum_types.h"

class JsonItem {
private:
    union {
        int data_int;
        double data_double;
        std::string *data_string;
    };
    DataType used_type;
public:

    // Constructors
    JsonItem(double data);
    JsonItem(int data);

    JsonItem(float data);
    JsonItem(std::string * data);
    JsonItem(std::string &&data);

    // operator overloading for cast
    operator int();
    operator float();
    operator double();
    operator std::string();

    //
    ~JsonItem();
};
#endif
