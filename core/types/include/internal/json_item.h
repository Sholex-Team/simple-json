#ifndef SIMPLE_JSON_JSON_ITEM_H
#define SIMPLE_JSON_JSON_ITEM_H
#include <string>
#include <vector>
#include "enum_types.h"
#include "json_type.h"

class JsonItem {
    typedef std::vector<JsonItem> type_array;

private:
    union {
        int data_int;
        double data_double;
        type_array * data_array;
        std::string * data_string;
        Json * data_json;
    };
    DataType used_type;
public:

    // Constructors
    JsonItem(double data);
    JsonItem(int data);
    JsonItem(type_array data);
    JsonItem(type_array && data);
    JsonItem(std::string data);
    JsonItem(std::string && data);
    JsonItem(Json data);
    JsonItem(Json &&data);
    JsonItem(const JsonItem &json_item);
    JsonItem(JsonItem &&json_item) noexcept;

    // Conversion operators for implicit & explicit conversions
    operator int() const;
    operator double() const;
    operator type_array() const;
    operator std::string() const;

    // Destructors
    ~JsonItem();
};
#endif
