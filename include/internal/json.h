#ifndef SIMPLE_JSON_JSON_H
#define SIMPLE_JSON_JSON_H

#include <ostream>
#include "enum_types.h"
#include "json_object.h"
#include "array_type.h"
#include "base_iterator.h"
#include "invalid_operation.h"
#include <string>

namespace simple_json::types {
    class JsonKey;
    class JsonObject;
    class Array;

    class Json {
    private:
        union {
            long int data_int;
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
        void create_object();
        void check_type(DataType) const;
    public:
        // Iterators
        class iterator : public iterators::JsonIterator {
        private:
            union {
                Array::iterator * array_iterator;
                JsonObject::iterator * json_object_iterator;
            };
        protected:
            void add_to_iterator() override;
        public:
            // Constructors
            iterator(const iterator &);
            iterator(iterator &&) noexcept;
            explicit iterator(const Array::iterator &);
            explicit iterator(const JsonObject::iterator &);

            // Operator Overloading
            Json & operator*() const;
            const iterator operator++(int);
            iterator & operator++();
            iterator operator+(int) const;
            iterator operator-(int) const;
            iterator operator+=(int);
            iterator operator-=(int);
            bool operator!=(const iterator &) const;

            // Public Methods
            const JsonKey & key() const override;
            Json & value() const;

            // Destructor
            ~iterator() noexcept override;
        };

        class const_iterator : public iterators::JsonIterator {
        private:
            const union {
                Array::const_iterator * array_iterator;
                JsonObject::const_iterator * json_object_iterator;
            };
        protected:
            void add_to_iterator() override;
        public:
            // Constructors
            const_iterator(const const_iterator &);
            const_iterator(const_iterator &&) noexcept;
            explicit const_iterator(const JsonObject::const_iterator &);
            explicit const_iterator(const Array::const_iterator &);

            // Operators
            const Json & operator*() const;
            const_iterator operator++(int);
            const_iterator & operator++();
            bool operator!=(const const_iterator &) const;

            // Public Methods
            const JsonKey & key() const override;
            const Json & value() const;

            // Destructor
            ~const_iterator() noexcept override;
        };

        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        JsonObject & items() const;

        // Constructors
        Json();
        Json(double);
        Json(long int);
        Json(bool);
        Json(std::nullptr_t t);
        explicit Json(Array);
        Json(Array &&);
        Json(const array_list_type &);
        Json(std::string);
        Json(std::string &&);
        Json(const char *);
        explicit Json(JsonObject);
        Json(JsonObject &&);
        Json(const json_list_type &);
        Json(const Json &);
        Json(Json &&) noexcept;
        explicit Json(DataType);

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
        Json & operator=(DataType);

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
        void push_back(const Json &);
        void insert(const pair_type &);
        void push_back(Json &&);
        void insert(pair_type &&);
        Json & back() const noexcept;
        inline DataType type() const noexcept {return used_type;}

        // Destructors
        ~Json();
    };

    std::ostream & operator<<(std::ostream &, const Json &);
}

#endif
