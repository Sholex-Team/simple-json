#ifndef SIMPLE_JSON_JSON_ITEM_H
#define SIMPLE_JSON_JSON_ITEM_H
#include <iostream>
#include <vector>
#include "enum_types.h"
#include "json_type.h"
#include "array_type.h"

class JsonItem {

private:
    union {
        int data_int;
        double data_double;
        bool data_boolean;
        Array * data_array;
        std::string * data_string;
        Json * data_json;
    };
    DataType used_type;

    void move(JsonItem & json_item) noexcept;

    void copy(const JsonItem & json_item);
public:
    // Constructors
    JsonItem();
    JsonItem(double data);
    JsonItem(int data);
    JsonItem(bool data);
    explicit JsonItem(Array data);
    JsonItem(Array && data);
    JsonItem(array_list_type & list_initial);
    JsonItem(array_list_type && list_initial);
    JsonItem(std::string data);
    explicit JsonItem(std::string && data);
    JsonItem(const char * data);
    JsonItem(Json data);
    explicit JsonItem(Json && data);
    JsonItem(json_list_type & initializer_list);
    JsonItem(json_list_type && initializer_list);
    JsonItem(const JsonItem & json_item);
    JsonItem(JsonItem && json_item) noexcept;

    // Conversion operators for implicit & explicit conversions
    operator int() const;
    operator double() const;
    operator Array() const;
    operator std::string() const;

    // Assignment Operator Overloading
    JsonItem & operator = (const JsonItem & json_item);
    JsonItem & operator = (JsonItem && json_item) noexcept;

    // Friends
    friend std::ostream & operator << (std::ostream & os, JsonItem && json_item);
    friend std::ostream & operator << (std::ostream & os, JsonItem & json_item);

    // Destructors
    ~JsonItem();
};

#endif
