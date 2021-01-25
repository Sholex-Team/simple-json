#ifndef SIMPLE_JSON_JSON_H
#define SIMPLE_JSON_JSON_H

#include <ostream>
#include "enum_types.h"
#include "json_object.h"
#include "array_type.h"
#include "json_patch.h"
#include "base_iterator.h"
#include "exceptions/invalid_operation.h"
#include <string>
#include "enum_types.h"
#include "exceptions/bad_conversion.h"
#include "exceptions/stream_exceptions.h"
#include "exceptions/iterator_exceptions.h"
#include <utility>
#include "exceptions/invalid_operator.h"
#include "json_utils.h"
#include "json_pointer.h"
#include <algorithm>
#include <functional>

namespace simple_json::types {
    class JsonKey;
    class JsonObject;
    class Array;
    class JsonPatch;

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
        void copy(const Json & json_item);
        void create_object();
        void check_type(const DataType target_type) const;
        inline void can_iterate() const {
            if (!(used_type == DataType::array_type || used_type == DataType::json_object_type)) {
                throw exceptions::InvalidOperation {};
            }
        }
        void clean_memory() noexcept;
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
            iterator(const iterator & r_iterator);
            iterator(iterator && r_iterator) noexcept;
            explicit iterator(const Array::iterator & array_iterator);
            explicit iterator(const JsonObject::iterator & json_object_iterator);

            // Operator Overloading
            Json & operator*() const;
            const iterator operator++(int);
            iterator & operator++();
            iterator operator+(size_t i) const;
            iterator operator-(size_t i) const;
            iterator operator+=(size_t i);
            iterator operator-=(size_t i);
            bool operator!=(const iterator & r_iterator) const;
            bool operator==(const iterator & r_iterator) const;

            // Public Methods
            const JsonKey & key() const override;
            Json & value() const;

            // Destructor
            ~iterator() noexcept override;

            // Friends
            friend Json;
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
            const_iterator(const const_iterator & r_iterator);
            const_iterator(const_iterator && r_iterator) noexcept;
            explicit const_iterator(const JsonObject::const_iterator & json_object_iterator);
            explicit const_iterator(const Array::const_iterator & array_iterator);

            // Operators
            const Json & operator*() const;
            const_iterator operator++(int);
            const_iterator & operator++();
            const_iterator operator+(size_t i) const;
            const_iterator operator-(size_t i) const;
            const_iterator operator+=(size_t i);
            const_iterator operator-=(size_t i);
            bool operator!=(const const_iterator & r_iterator) const;
            bool operator==(const const_iterator & r_iterator) const;

            // Public Methods
            const JsonKey & key() const override;
            const Json & value() const;

            // Destructor
            ~const_iterator() noexcept override;

            // Friends
            friend Json;
        };

        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;
        JsonObject & items() const;

        // Constructors
        Json();
        Json(double data);
        Json(long int data);
        Json(bool data);
        Json(int data);
        Json(std::nullptr_t data);
        explicit Json(const Array & data);
        Json(Array && data);
        Json(const array_list_type & list_initial);
        Json(std::string &);
        Json(std::string &&);
        Json(const char *);
        explicit Json(JsonObject);
        Json(JsonObject &&);
        Json(const json_list_type & initializer_list);
        Json(const Json & json_item);
        Json(Json && json_item) noexcept;
        explicit Json(DataType object_type);

        // Conversion operators for implicit & explicit conversions
        explicit operator long int() const;
        explicit operator double() const;
        explicit operator Array() const;
        explicit operator std::string() const;
        explicit operator JsonObject() const;
        explicit operator const char *() const;

        // Assignment Operator Overloading
        Json & operator=(const Json &);
        Json & operator=(Json &&) noexcept;
        Json & operator=(const json_list_type & json_object_list);
        Json & operator=(const array_list_type & array_list);
        Json & operator=(DataType object_type);

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const Json & json_item);
        friend JsonObject;
        friend Array;
        friend JsonPatch;

        // Operator Overloading
        Json & operator[](const size_t & index);
        Json & operator[](const char * & index);
        Json & operator[](const JsonKey & index);
        Json & operator[](const JsonPointer & json_pointer);
        bool operator==(const Json & json_item) const;
        bool operator!=(const Json & json_item) const;

        // Public Method
        Json & at(size_t);
        Json & at(const std::string &);
        Json & at(const JsonPointer &);
        Json & at(const JsonKey &);
        const_iterator get_item(size_t index) const;
        JsonPatch get_diff(const Json & dst) const;
        void erase(size_t);
        void erase(const std::string &);
        void erase(const JsonKey &);
        void erase(const JsonPointer &);
        void push_back(const Json &);
        void insert(const pair_type &);
        void insert(pair_type &&);
        void insert(const const_iterator & position, const Json & item);
        void insert(const const_iterator & position, Json && item);
        void push_back(Json &&);
        Json & back() const noexcept;
        inline DataType type() const noexcept {return used_type;}
        bool empty() const;
        std::string serialize() const;
        size_t count(const JsonKey & key) const;
        size_t count(const Json & item) const;
        bool contains(const JsonKey & key) const;
        iterator find(const JsonKey & key);
        iterator find(const Json & item);
        const_iterator find(const JsonKey & key) const;
        const_iterator find(const Json & item) const;
        iterator find_if(const std::function<bool(const Json &)> & test_func);
        const_iterator find_if(const std::function<bool(const Json &)> & test_func) const;
        iterator find_if(const std::function<bool(const pair_type &)> & test_func);
        const_iterator find_if(const std::function<bool(const pair_type &)> & test_func) const;
        size_t find_index(const Json & item) const;
        size_t find_index(const const_iterator & it) const;
        size_t size() const noexcept;
        void update(const Json & target);

        template<typename T>
        T find_in_range(const T & first, const T & last, const Json & item) const {
            first.check_type(IteratorTypes::array_iterator_type);
            last.check_type(IteratorTypes::array_iterator_type);
            return T {std::find(* first.array_iterator, * last.array_iterator, item)};
        }

        template<typename T>
        size_t count_in_range(const T & first, const T & last, const Json & item) const {
            first.check_type(IteratorTypes::array_iterator_type);
            last.check_type(IteratorTypes::array_iterator_type);
            return std::count(* first.array_iterator, * last.array_iterator, item);
        }

        // Destructors
        ~Json();
    };

    std::ostream & operator<<(std::ostream & os, const Json & json_item);
}

#endif
