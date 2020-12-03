#ifndef SIMPLE_JSON_BASE_TYPE_H
#define SIMPLE_JSON_BASE_TYPE_H
#include <string>
#include "enum_types.h"
class JsonItem {
private:
    union {
        unsigned int data_u_i;
        unsigned short data_u_s;
        short data_short;
        int data_int;
        double data_double;
        float data_float;
        std::string data_string;
    };
    DataType used_type;
public:
    JsonItem(double data);

    JsonItem(int data);

    JsonItem(float data);

    JsonItem(short data);

    JsonItem(unsigned short data);

    JsonItem(unsigned int data);

    JsonItem(std::string data);

    JsonItem(std::string &&data);

    operator int();

    ~JsonItem() {}
};
#endif
