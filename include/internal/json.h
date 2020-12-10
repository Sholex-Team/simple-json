#ifndef SIMPLE_JSON_JSON_H
#define SIMPLE_JSON_JSON_H

#include <ostream>
#include "enum_types.h"
#include "json_object.h"
#include "array_type.h"

namespace simple_json::types {
    class JsonKey;
    class JsonObject;
    class Array;

    class Json {
    private:
        union {
            int data_int;
            double data_double;
            bool data_boolean;
            Array * data_array;
            std::string * data_string;
            JsonObject * data_json_object;
        };
        DataType used_type;

        // Private Method
        void move(Json &) noexcept;
        void copy(const Json &);
    public:
        // Iterators
        class iterator {
        private:
            union {
                Array::iterator * array_iterator;
                JsonObject::iterator * json_object_iterator;
            };

            IteratorTypes used_type;
        public:
            // Constructors
            iterator(const iterator &);
            iterator(iterator &&) noexcept;
            explicit iterator(const Array::iterator &);
            explicit iterator(const JsonObject::iterator &);

            // Public Methods
            Json & operator*() const;
            const iterator operator++(int);
            iterator & operator++();
            bool operator!=(const iterator &) const;
        };

        iterator begin();
        iterator end();

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
        Json & operator=(json_list_type &);
        Json & operator=(array_list_type &);

        // Friends
        friend std::ostream & operator<<(std::ostream &, const Json &);
        friend JsonObject;
        friend Array;

        // Operator Overloading
        Json & operator[](const int &);
        Json & operator[](const char * &);
        bool operator==(const Json &) const;
        bool operator==(const Json &&) const;

        // Public Method
        Json & at(int);
        Json & at(const char *);

        // Destructors
        ~Json();
    };

    std::ostream & operator<<(std::ostream &, const Json &);
}

#endif
