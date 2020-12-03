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
    JsonItem(double data);

    JsonItem(int data);

    JsonItem(std::string * data);

    JsonItem(std::string &&data);

    operator int() const;

    ~JsonItem();
};
#endif
