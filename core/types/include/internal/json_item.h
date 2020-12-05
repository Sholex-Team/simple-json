#ifndef SIMPLE_JSON_JSON_ITEM_H
#define SIMPLE_JSON_JSON_ITEM_H
#include <ostream>
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

    // Private Method
    void move(JsonItem &) noexcept;
    void copy(const JsonItem &);
public:
    // Constructors
    JsonItem();
    JsonItem(double);
    JsonItem(int);
    JsonItem(bool);
    JsonItem(std::nullptr_t t);
    explicit JsonItem(Array);
    JsonItem(Array &&);
    JsonItem(array_list_type &);
    JsonItem(array_list_type &&);
    explicit JsonItem(std::string);
    JsonItem(std::string &&);
    JsonItem(const char *);
    explicit JsonItem(Json);
    JsonItem(Json &&);
    JsonItem(json_list_type &);
    JsonItem(json_list_type &&);
    JsonItem(const JsonItem &);
    JsonItem(JsonItem &&) noexcept;

    // Conversion operators for implicit & explicit conversions
    operator int() const;
    operator double() const;
    operator Array() const;
    operator std::string() const;
    operator Json() const;

    // Assignment Operator Overloading
    JsonItem & operator=(const JsonItem &);
    JsonItem & operator=(JsonItem &&) noexcept;

    // Friends
    friend std::ostream & operator<<(std::ostream &, JsonItem &&);
    friend std::ostream & operator<<(std::ostream &, JsonItem &);

    // Operator [] Overloading
    JsonItem & operator [](const int &);
    JsonItem & operator [](const char *);

    // Public Method
    JsonItem & at(const int);
    JsonItem & at(const char *);

    // Destructors
    ~JsonItem();
};

#endif
