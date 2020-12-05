#ifndef SIMPLE_JSON_JSON_H
#define SIMPLE_JSON_JSON_H

#include <ostream>
#include <vector>
#include "enum_types.h"
#include "json_object.h"
#include "array_type.h"
#include "json_key.h"

namespace simple_json::types {
    class Json {
    private:
        union {
            int data_int;
            double data_double;
            bool data_boolean;
            Array * data_array;
            std::string * data_string;
            JsonObject * data_json;
        };
        DataType used_type;

        // Private Method
        void move(Json &) noexcept;
        void copy(const Json &);
    public:
        // Constructors
        Json();
        Json(double);
        Json(int);
        Json(bool);
        Json(std::nullptr_t t);
        explicit Json(Array);
        Json(Array &&);
        Json(array_list_type &);
        Json(array_list_type &&);
        Json(std::string);
        Json(std::string &&);
        Json(const char *);
        explicit Json(JsonObject);
        Json(JsonObject &&);
        Json(json_list_type &);
        Json(json_list_type &&);
        Json(const Json &);
        Json(Json &&) noexcept;

        // Conversion operators for implicit & explicit conversions
        operator int() const;
        operator double() const;
        operator Array() const;
        operator std::string() const;
        operator JsonObject() const;

        // Assignment Operator Overloading
        Json & operator=(const Json &);
        Json & operator=(Json &&) noexcept;

        // Friends
        friend std::ostream & operator<<(std::ostream &, Json &&);
        friend std::ostream & operator<<(std::ostream &, Json &);

        // Operator [] Overloading
        Json & operator[](const int &);
        Json & operator[](const char * &);

        // Public Method
        Json & at(int);
        Json & at(const char *);

        // Destructors
        ~Json();
    };

    std::ostream & operator<<(std::ostream &, Json &);
    std::ostream & operator<<(std::ostream &, Json &&);
}

#endif
