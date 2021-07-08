#ifndef SIMPLE_JSON_JSON_H
#define SIMPLE_JSON_JSON_H

#include <ostream>
#include "enum_types.h"
#include "json_object.h"
#include "array_type.h"
#include "base_iterator.h"
#include "exceptions/invalid_operation.h"
#include <string>
#include "enum_types.h"
#include "exceptions/bad_conversion.h"
#include "exceptions/stream_exceptions.h"
#include "exceptions/wrong_type.h"
#include "exceptions/iterator_exceptions.h"
#include <utility>
#include "exceptions/invalid_operator.h"
#include "../json_utils.h"
#include "json_pointer.h"
#include <algorithm>
#include <functional>
#include "exceptions/invalid_merge.h"
#include <type_traits>

namespace simple_json::types {
    class JsonKey;
    class JsonObject;
    class Array;
    class JsonPatch;

    // Functions
    namespace {
        void apply_merge_patch(Json & current_item, const Json & current_patch) noexcept;
    }

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
        void check_type(DataType target_type) const;
        inline void can_iterate() const {
            if (!(used_type == DataType::array_type || used_type == DataType::json_object_type)) {
                throw exceptions::InvalidOperation {};
            }
        }
        void clean_memory() noexcept;
        void increment();
        void decrement();
        void is_numeric() const;
        void check_operator(DataType target_type) const;
        void check_data(DataType target_type) const;
    public:
        // Iterators

        /*!
         * @brief Json Iterator class.
         *
         * This class is used to create an iterator for a Json object.
         */
        class iterator : public iterators::JsonIterator {
        private:
            union {
                Array::iterator * array_iterator;
                JsonObject::iterator * json_object_iterator;
            };
        protected:
            void increment_iterator() override;
            void decrement_iterator() override;
        public:
            // Constructors
            /*!
             * @brief iterator class copy constructor.
             *
             * This constructor creates and iterator from an iterator reference. it actually copies the iterator
             * passed to it.
             * @param r_iterator iterator object which is going to be copied.
             */
            iterator(const iterator & r_iterator);

            /*!
             * @brief iterator class move constructor.
             *
             * This move constructor creates a new iterator object and moves the data within iterator which it's
             * r-value reference is passed to it into the new object.
             * @param r_iterator A r-value reference to iterator object which is about to be moved.
             */
            iterator(iterator && r_iterator) noexcept;

            /*!
             * @brief iterator class constructor.
             *
             * This constructor creates an iterator object based on an Array::iterator.
             * @param array_iterator Array::iterator which is going to be used to create an iterator object.
             */
            explicit iterator(const Array::iterator & array_iterator);

            /*!
             * @brief iterator class constructor.
             *
             * This constructor creates an iterator object based on a JsonObject::iterator.
             * @param json_object_iterator JsonObject::iterator which is going to be used to create an iterator object.
             */
            explicit iterator(const JsonObject::iterator & json_object_iterator);

            // Operator Overloading
            /*!
             * @brief iterator dereference operator overload.
             * @throw iterators::exceptions::InvalidDereference Throws when the type of the base iterator is not
             * Array::iterator.
             * @return Json object which the iterator is pointing to.
             */
            Json & operator*() const;

            /*!
             * @brief iterator post-increment operator overload.
             *
             * This operator copies the iterator object and increments the original iterator by one position.
             * @return A const copy of iterator object before incrementing.
             */
            const iterator operator++(int);

            /*!
             * @brief iterator pre-increment operator overload.
             *
             * This operator increments the iterator by one position.
             * @return A reference to Incremented operator.
             */
            iterator & operator++();

            /*!
             * @brief iterator post-decrement operator overload.
             *
             * This operator copies the iterator object and decrements the original iterator by one position.
             * @return A const copy of iterator object before decrementing.
             */
            const iterator operator--(int);

            /*!
             * @brief iterator pre-decrement operator overload.
             *
             * This operator decrements the iterator by one position.
             * @return A reference to decremented operator.
             */
            iterator & operator--();

            /*!
             * @brief iterator addition operator overload.
             *
             * This operator copies the iterator object and increments the copy by specified positions.
             * @param i Positions that the iterator is going to get incremented by.
             * @return Incremented iterator object.
             */
            iterator operator+(long i) const;

            /*!
             * @brief iterator subtraction operator overload.
             *
             * This operator copies the iterator object and decrements the copy by given positions.
             * @param i Positions that the iterator is going to get decremented by.
             * @return Decremented iterator object.
             */
            iterator operator-(long i) const;

            /*!
             * @brief iterator addition assignment operator overload.
             *
             * This operator increments the iterator by given positions.
             * @param i Positions that the iterator is going to get incremented by.
             * @return Incremented iterator.
             */
            iterator & operator+=(long i);

            /*!
             * @brief iteration subtraction assignment operator overload.
             *
             * This operator decrements the iterator by given positions.
             * @param i Positions that the iterator it going to get decremented by.
             * @return Decremented iterator.
             */
            iterator & operator-=(long i);

            /*!
             * @brief Not equal to operator overload.
             *
             * This operator checks if iterator is not equal to given operator.
             * @param r_iterator The iterator object which is going to get compared.
             * @return Boolean representing the checking result.
             */
            bool operator!=(const iterator & r_iterator) const;

            /*!
             * @brief equality operator overload.
             *
             * This operator checks if iterator is equal to a given iterator.
             * @param r_iterator The iterator object which is going to get compared.
             * @return Boolean representing the checking result.
             */
            bool operator==(const iterator & r_iterator) const;

            iterator & operator=(const iterator & r_iterator);
            iterator & operator=(iterator && r_iterator) noexcept;

            // Public Methods
            /*!
             * @brief Returns the JsonKey object.
             *
             * Returns the JsonKey object representing the key of std::pair that the iterator is pointing to.
             * @throw iterators::exceptions::InvalidType Throws if the iterator is not a JsonObject iterator.
             * @return A const reference to the JsonKey object.
             */
            const JsonKey & key() const override;

            /*!
             * @brief Returns the Json object.
             *
             * Returns the Json object of the std::pair that the iterator is pointing to.
             * @throw iterators::exceptions::InvalidType Throws if the iterator is not a JsonObject iterator.
             * @return A reference to value inside std::pair.
             */
            Json & value() const;

            // Destructor
            /*!
             * @brief iterator destructor
             *
             * Checks the iterator type and deletes the iterator union member based on it.
             */
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
            void increment_iterator() override;
            void decrement_iterator() override;
        public:
            // Constructors

            /*!
             * @brief const_iterator copy constructor.
             *
             * Copies the const_iterator passed to it into a new const_iterator object.
             * @param r_iterator const_iterator object that is going to get copied.
             */
            const_iterator(const const_iterator & r_iterator);

            /*!
             * @brief const_iterator move constructor.
             *
             * Moves the const_iterator object passed to it into a new const_iterator object.
             * @param r_iterator const_iterator object which is about to be moved.
             */
            const_iterator(const_iterator && r_iterator) noexcept;

            /*!
             * @brief const_iterator JsonObject::iterator constructor.
             *
             * Creates a new const_iterator based on a JsonObject::const_iterator object passed to it.
             * @param json_object_iterator A const reference to the JsonObject::const_iterator that is going to be
             * used for creating a new
             * const_iterator object.
             */
            explicit const_iterator(const JsonObject::const_iterator & json_object_iterator);

            /*!
             * @brief const_iterator Array::const_iterator constructor.
             *
             * Creates a new const_iterator object based on a Array::const_iterator object passed to it.
             * @param array_iterator A const reference to the Array::const_iterator object which is about to be
             * used as base.
             */
            explicit const_iterator(const Array::const_iterator & array_iterator);

            // Operator Overloading

            /*!
             * @brief const_iterator dereference operator overload.
             * @throw iterators::exceptions::InvalidDereference Throws when the type of the base const_iterator is not
             * Array::const_iterator.
             * @return Json object which the iterator is pointing to.
             */
            const Json & operator*() const;

            /*!
             * @brief const_iterator post-increment operator overload.
             *
             * Copies the const_iterator and increments the original const_iterator object and returns the copy.
             * @return A copied const_iterator object of the original one before incrementing.
             */
            const const_iterator operator++(int);

            /*!
             * @brief const_iterator pre-increment operator overload.
             *
             * increments the const_iterator object by one position.
             * @return A reference to incremented const_iterator object.
             */
            const_iterator & operator++();

            /*!
             * @brief const_iterator post-decrement operator overload.
             *
             * Copies the const_iterator and decrements the original const_iterator object and returns the copy.
             * @return A copied const_iterator object of the original one before decrementing.
             */
            const const_iterator operator--(int);

            /*!
             * @brief const_iterator pre-decrement operator overload.
             *
             * Decrements the const_iterator object by one position.
             * @return A reference to decremented const_iterator object.
             */
            const_iterator & operator--();


            /*!
             * @brief const_iterator addition operator.
             *
             * Copies the const_iterator and increments the copy by given positions.
             * @param i Positions that the copied const_iterator object is going to get incremented by.
             * @return Incremented copy of const_iterator object.
             */
            const_iterator operator+(long i) const;

            /*!
             * @brief const_iterator subtraction operator.
             *
             * Copies the const_iterator object and decrements the copy by given positions.
             * @param i Positions that the copied const_iterator object is going to get decremented by.
             * @return Decremented copy of const_iterator object.
             */
            const_iterator operator-(long i) const;

            /*!
             * @brief const_iterator addition assignment operator overload.
             *
             * increments the const_iterator object by given positions.
             * @param i Positions and the const_iterator object is going to get incremented by.
             * @return A reference to Incremented const_iterator object.
             */
            const_iterator & operator+=(long i);

            /*!
             * @brief const_iterator subtractions assignment operator overload.
             *
             * Moves the const_iterator object back by given positions.
             * @param i Positions that the const_iterator object to going to get decremented by.
             * @return A reference to Decremented const_iterator object.
             */
            const_iterator & operator-=(long i);

            /*!
             * @brief Checks if the const_iterator is not equal to given const_iterator object reference.
             * @param r_iterator A const reference to const_iterator object which is going to get compared.
             * @return Result of comparison.
             */
            bool operator!=(const const_iterator & r_iterator) const;

            /*!
             * @brief Check is the const_iterator is equal to given const_iterator object reference.
             * @param r_iterator A const reference to const_iterator object which is going to get compared.
             * @return Result of comparison.
             */
            bool operator==(const const_iterator & r_iterator) const;

            const_iterator & operator=(const const_iterator & r_iterator);
            const_iterator & operator=(const_iterator && r_iterator) noexcept;

            // Public Methods
            /*!
             * @brief Returns the key of object that the const_iterator is pointing to.
             *
             * This method returns a const reference to the key(first item) of the std::pair that the const_iterator is
             * pointing to within a JsonObject.
             * @return A const reference to a JsonKey object.
             */
            const JsonKey & key() const override;

            /*!
             * @brief Returns the value of object that the const_iterator is pointing to.
             *
             * This method returns a const reference to the value(second item) of the std::pair that the const_iterator
             * is pointing to within a JsonObject.
             * @return A const reference to a Json object.
             */
            const Json & value() const;

            // Destructor

            /*!
             * @brief const_iterator destructor
             *
             * Checks the const_iterator type and deletes the iterator union member based on it.
             */
            ~const_iterator() noexcept override;

            // Friends
            friend Json;
        };

        class reverse_iterator : public iterators::JsonIterator {
        private:
            const union {
                Array::reverse_iterator * array_iterator;
                JsonObject::reverse_iterator * json_object_iterator;
            };
        protected:
            void increment_iterator() override;
            void decrement_iterator() override;
        public:
            // Constructors

            /*!
             * @brief reverse_iterator copy constructor.
             *
             * Copies the reverse_iterator passed to it into a new reverse_iterator object.
             * @param r_iterator reverse_iterator object that is going to get copied.
             */
            reverse_iterator(const reverse_iterator & r_iterator);

            /*!
             * @brief reverse_iterator move constructor.
             *
             * Moves the reverse_iterator object passed to it into a new reverse_iterator object.
             * @param r_iterator reverse_iterator object which is about to be moved.
             */
            reverse_iterator(reverse_iterator && r_iterator) noexcept;

            /*!
             * @brief reverse_iterator JsonObject::iterator constructor.
             *
             * Creates a new reverse_iterator based on a JsonObject::reverse_iterator object passed to it.
             * @param json_object_iterator A const reference to the JsonObject::reverse_iterator that is
             * going to be used for creating a new
             * reverse_iterator object.
             */
            explicit reverse_iterator(const JsonObject::reverse_iterator & json_object_iterator);

            /*!
             * @brief reverse_iterator Array::reverse_iterator constructor.
             *
             * Creates a new reverse_iterator object based on a Array::reverse_iterator object passed to it.
             * @param array_iterator A const reference to the Array::reverse_iterator object which is about
             * to be used as base.
             */
            explicit reverse_iterator(const Array::reverse_iterator & array_iterator);

            // Operator Overloading

            /*!
             * @brief reverse_iterator dereference operator overload.
             * @throw iterators::exceptions::InvalidDereference Throws when the type of the base
             * reverse_iterator is not Array::reverse_iterator.
             * @return Json object which the iterator is pointing to.
             */
            Json & operator*() const;

            /*!
             * @brief reverse_iterator post-increment operator overload.
             *
             * Copies the reverse_iterator and increments the original reverse_iterator object and
             * returns the copy.
             * @return A copied reverse_iterator object of the original one before incrementing.
             */
            const reverse_iterator operator++(int);

            /*!
             * @brief reverse_iterator pre-increment operator overload.
             *
             * increments the reverse_iterator object by one position.
             * @return A reference to Incremented reverse_iterator object.
             */
            reverse_iterator & operator++();
            
            /*!
             * @brief reverse_iterator post-decrement operator overload.
             *
             * Copies the reverse_iterator and decrements the original reverse_iterator object and
             * returns the copy.
             * @return A copied reverse_iterator object of the original one before decrementing.
             */
            const reverse_iterator operator--(int);

            /*!
             * @brief reverse_iterator pre-decrement operator overload.
             *
             * decrements the reverse_iterator object by one position.
             * @return A reference to decremented reverse_iterator object.
             */
            reverse_iterator & operator--();

            /*!
             * @brief reverse_iterator addition operator.
             *
             * Copies the reverse_iterator and increments the copy by given positions.
             * @param i Positions that the copied reverse_iterator object is going to get incremented by.
             * @return Incremented copy of reverse_iterator object.
             */
            reverse_iterator operator+(long i) const;

            /*!
             * @brief reverse_iterator subtraction operator.
             *
             * Copies the reverse_iterator object and moves the copy back by given positions.
             * @param i Positions that the copied reverse_iterator object is going to get decremented by.
             * @return Decremented copy of reverse_iterator object.
             */
            reverse_iterator operator-(long i) const;

            /*!
             * @brief reverse_iterator addition assignment operator overload.
             *
             * increments the reverse_iterator object by given positions.
             * @param i Positions and the reverse_iterator object is going to get incremented by.
             * @return A reference to Incremented reverse_iterator object.
             */
            reverse_iterator & operator+=(long i);

            /*!
             * @brief reverse_iterator subtractions assignment operator overload.
             *
             * Moves the reverse_iterator object back by given positions.
             * @param i Positions that the reverse_iterator object to going to get decremented by.
             * @return A reference to Decremented reverse_iterator object.
             */
            reverse_iterator & operator-=(long i);

            /*!
             * @brief Checks if the reverse_iterator is not equal to given reverse_iterator object reference.
             * @param r_iterator A const reference to reverse_iterator object which is going to get compared.
             * @return Result of comparison.
             */
            bool operator!=(const reverse_iterator & r_iterator) const;

            /*!
             * @brief Check is the reverse_iterator is equal to given reverse_iterator object reference.
             * @param r_iterator A const reference to reverse_iterator object which is going to get compared.
             * @return Result of comparison.
             */
            bool operator==(const reverse_iterator & r_iterator) const;

            // Public Methods
            /*!
             * @brief Returns the key of object that the reverse_iterator is pointing to.
             *
             * This method returns a const reference to the key(first item) of the std::pair that the
             * reverse_iterator is pointing to within a JsonObject.
             * @return A const reference to a JsonKey object.
             */
            const JsonKey & key() const override;

            /*!
             * @brief Returns the value of object that the reverse_iterator is pointing to.
             *
             * This method returns a const reference to the value(second item) of the std::pair that the
             * reverse_iterator is pointing to within a JsonObject.
             * @return A const reference to a Json object.
             */
            Json & value() const;

            // Destructor

            /*!
             * @brief reverse_iterator destructor
             *
             * Checks the reverse_iterator type and deletes the iterator union member based on it.
             */
            ~reverse_iterator() noexcept override;

            // Friends
            friend Json;
        };

        class const_reverse_iterator : public iterators::JsonIterator {
        private:
            const union {
                Array::const_reverse_iterator * array_iterator;
                JsonObject::const_reverse_iterator * json_object_iterator;
            };
        protected:
            void increment_iterator() override;
            void decrement_iterator() override;
        public:
            // Constructors

            /*!
             * @brief const_reverse_iterator copy constructor.
             *
             * Copies the const_reverse_iterator passed to it into a new const_reverse_iterator object.
             * @param r_iterator const_reverse_iterator object that is going to get copied.
             */
            const_reverse_iterator(const const_reverse_iterator & r_iterator);

            /*!
             * @brief const_reverse_iterator move constructor.
             *
             * Moves the const_reverse_iterator object passed to it into a new const_reverse_iterator object.
             * @param r_iterator const_reverse_iterator object which is about to be moved.
             */
            const_reverse_iterator(const_reverse_iterator && r_iterator) noexcept;

            /*!
             * @brief const_reverse_iterator JsonObject::iterator constructor.
             *
             * Creates a new const_reverse_iterator based on a JsonObject::const_reverse_iterator object passed to it.
             * @param json_object_iterator A const reference to the JsonObject::const_reverse_iterator that is
             * going to be used for creating a new
             * const_reverse_iterator object.
             */
            explicit const_reverse_iterator(const JsonObject::const_reverse_iterator & json_object_iterator);

            /*!
             * @brief const_reverse_iterator Array::const_reverse_iterator constructor.
             *
             * Creates a new const_reverse_iterator object based on a Array::const_reverse_iterator object passed to it.
             * @param array_iterator A const reference to the Array::const_reverse_iterator object which is about to be
             * used as base.
             */
            explicit const_reverse_iterator(const Array::const_reverse_iterator & array_iterator);

            // Operator Overloading

            /*!
             * @brief const_reverse_iterator dereference operator overload.
             * @throw iterators::exceptions::InvalidDereference Throws when the type of the base
             * const_reverse_iterator is not Array::const_reverse_iterator.
             * @return Json object which the iterator is pointing to.
             */
            const Json & operator*() const;

            /*!
             * @brief const_reverse_iterator post-increment operator overload.
             *
             * Copies the const_reverse_iterator and increments the original const_reverse_iterator object and
             * returns the copy.
             * @return A copied const_reverse_iterator object of the original one before incrementing.
             */
            const const_reverse_iterator operator++(int);

            /*!
             * @brief const_reverse_iterator pre-increment operator overload.
             *
             * increments the const_reverse_iterator object by one position.
             * @return A reference to Incremented const_reverse_iterator object.
             */
            const_reverse_iterator & operator++();

            /*!
             * @brief const_reverse_iterator post-decrement operator overload.
             *
             * Copies the const_reverse_iterator and decrements the original const_reverse_iterator object and
             * returns the copy.
             * @return A copied const_reverse_iterator object of the original one before decrementing.
             */
            const const_reverse_iterator operator--(int);

            /*!
             * @brief const_reverse_iterator pre-decrement operator overload.
             *
             * decrements the const_reverse_iterator object by one position.
             * @return A reference to decremented const_reverse_iterator object.
             */
            const_reverse_iterator & operator--();

            /*!
             * @brief const_reverse_iterator addition operator.
             *
             * Copies the const_reverse_iterator and increments the copy by given positions.
             * @param i Positions that the copied const_reverse_iterator object is going to get incremented by.
             * @return Incremented copy of const_reverse_iterator object.
             */
            const_reverse_iterator operator+(long i) const;

            /*!
             * @brief const_reverse_iterator subtraction operator.
             *
             * Copies the const_reverse_iterator object and moves the copy back by given positions.
             * @param i Positions that the copied const_reverse_iterator object is going to get decremented by.
             * @return Decremented copy of const_reverse_iterator object.
             */
            const_reverse_iterator operator-(long i) const;

            /*!
             * @brief const_reverse_iterator addition assignment operator overload.
             *
             * increments the const_reverse_iterator object by given positions.
             * @param i Positions and the const_reverse_iterator object is going to get incremented by.
             * @return A reference to Incremented const_reverse_iterator object.
             */
            const_reverse_iterator & operator+=(long i);

            /*!
             * @brief const_reverse_iterator subtractions assignment operator overload.
             *
             * Moves the const_reverse_iterator object back by given positions.
             * @param i Positions that the const_reverse_iterator object to going to get decremented by.
             * @return A reference to Decremented const_reverse_iterator object.
             */
            const_reverse_iterator & operator-=(long i);

            /*!
             * @brief Checks if the const_reverse_iterator is not equal to given const_reverse_iterator object reference.
             * @param r_iterator A const reference to const_reverse_iterator object which is going to get compared.
             * @return Result of comparison.
             */
            bool operator!=(const const_reverse_iterator & r_iterator) const;

            /*!
             * @brief Check is the const_reverse_iterator is equal to given const_reverse_iterator object reference.
             * @param r_iterator A const reference to const_reverse_iterator object which is going to get compared.
             * @return Result of comparison.
             */
            bool operator==(const const_reverse_iterator & r_iterator) const;

            const_reverse_iterator & operator=(const const_reverse_iterator & r_iterator);
            const_reverse_iterator & operator=(const_reverse_iterator && r_iterator) noexcept;

            // Public Methods
            /*!
             * @brief Returns the key of object that the const_reverse_iterator is pointing to.
             *
             * This method returns a const reference to the key(first item) of the std::pair that the
             * const_reverse_iterator is pointing to within a JsonObject.
             * @return A const reference to a JsonKey object.
             */
            const JsonKey & key() const override;

            /*!
             * @brief Returns the value of object that the const_reverse_iterator is pointing to.
             *
             * This method returns a const reference to the value(second item) of the std::pair that the
             * const_reverse_iterator is pointing to within a JsonObject.
             * @return A const reference to a Json object.
             */
            const Json & value() const;

            // Destructor

            /*!
             * @brief const_reverse_iterator destructor
             *
             * Checks the const_reverse_iterator type and deletes the iterator union member based on it.
             */
            ~const_reverse_iterator() noexcept override;

            // Friends
            friend Json;
        };

        // Constructors
        /*!
         * @brief Json default constructor.
         *
         * Creates a Json object with an empty JsonObject within.
         */
        Json();

        /*!
         * @brief Json double data type constructor.
         * @param data double data
         */
        Json(double data);

        /*!
         * @brief Json long int data type constructor.
         * @param data long int data
         */
        Json(long int data);

        /*!
         * @brief Json bool data type constructor.
         * @param data bool data
         */
        Json(bool data);

        /*!
         * @brief Json int data type constructor.
         * @param data int data
         */
        Json(int data);

        /*!
         * @brief Json null constructor.
         * @param data std::nullptr_t data.
         */
        Json(std::nullptr_t data);

        /*!
         * @brief Json Array constructor.
         * @param data Const reference to Array data.
         */
        explicit Json(const Array & data);

        /*!
         * @brief Json Array constructor.
         * @param data A r-value reference to Array data.
         */
        Json(Array && data);

        /*!
         * @brief Json Array initializer_list constructor.
         * @param initializer_list A const reference to an Array initializer-List data.
         */
        Json(const array_list_type & initializer_list);

        /*!
         * @brief Json std::string constructor.
         * @param data A const reference to std::string data.
         */
        Json(const std::string & data);

        /*!
         * @brief Json std::string constructor.
         * @param data A r-value reference to std::string data.
         */
        Json(std::string && data);

        /*!
         * @brief Json c-string constructor.
         * @param data const char pointer pointing to the first character of c-string.
         */
        Json(const char * data);

        /*!
         * @brief Json JsonObject constructor.
         * @param data A const reference to JsonObject data.
         */
        explicit Json(const JsonObject & data);

        /*!
         * @brief Json JsonObject constructor.
         * @param data A r-value reference to JsonObject data.
         */
        Json(JsonObject && data);

        /*!
         * @brief Json JsonObject initializer_list constructor.
         * @param initializer_list A const reference to JsonObject initializer_list.
         */
        Json(const json_list_type & initializer_list);

        /*!
         * @brief Json copy constructor.
         *
         * Copies a Json object into a new Json object.
         * @param json_item A reference to Json object which is about to get copied.
         */
        Json(const Json & json_item);

        /*!
         * @brief Json move constructor.
         *
         * Moves a Json object into a new Json object.
         * @param json_item A r-value reference to Json which is about to be moved.
         */
        Json(Json && json_item) noexcept;

        /*!
         * @brief Json data type constructor.
         *
         * Creates a new empty Json object based on the given data type.
         * @param object_type Data type which is about to be used to create an empty Json object.
         */
        explicit Json(DataType object_type);

        // Explicit conversion operators
        /*!
         * @brief Json to long int conversion operator.
         * @return int data
         */
        explicit operator long int() const;

        /*!
         * @brief Json to double conversion operator.
         * @return double data
         */
        explicit operator double() const;

        /*!
         * @brief Json to Array conversion operator.
         * @return Array data
         */
        explicit operator Array() const;

        /*!
         * @brief Json to std::string conversion operator.
         * @return std::string data
         */
        explicit operator std::string() const;

        /*!
         * @brief Json to JsonObject conversion operator.
         * @return JsonObject data
         */
        explicit operator JsonObject() const;

        /*!
         * @brief Json to const c-string conversion operator.
         * @return Const pointer to first character of c-string data.
         */

        // Operator Overloading

        explicit operator const char * () const;

        /*!
         * @brief Json copy assignment operator overload.
         *
         * Assigns a copy of a Json object as the data stored inside Json object.
         * @param data A const reference to Json object which is about to get copied.
         * @return A reference to modified Json object.
         */
        Json & operator=(const Json & data);

        /*!
         * @brief Json move assignment operator overload.
         *
         * Moves a Json object into the current Json object.
         * @param data A r-value reference to Json object which is about ot be moved.
         * @return A reference to modified Json object.
         */
        Json & operator=(Json && data) noexcept;

        /*!
         * @brief Json JsonObject initializer_list assignment operator overload.
         *
         * Assigns a JsonObject to the the current Json object using given initializer_list.
         * @param initializer_list JsonObject initializer_list containing items inside a JsonObject.
         * @return A reference to modified Json object.
         */
        Json & operator=(const json_list_type & initializer_list);

        /*!
         * @brief Json Array initializer_list assignment operator overload.
         *
         * Assigns a Array to the the current Json object using given initializer_list.
         * @param initializer_list Array initializer_list containing items inside a JsonObject.
         * @return A reference to modified Json object.
         */
        Json & operator=(const array_list_type & initializer_list);

        /*!
         * @brief Json DataType assignment operator overload.
         *
         * Creates an empty Json object with given DataType and assigns it to the current Json object.
         * @param object_type A reference to modified Json object.
         * @return
         */
        Json & operator=(DataType object_type);

        /*!
         * @brief Json long integer addition assignment operator
         * @param rhs Right hand side long integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator+=(long rhs);

        /*!
         * @brief Json integer addition assignment operator
         * @param rhs Right hand side integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator+=(int rhs);

        /*!
         * @brief Json double addition assignment operator
         * @param rhs Right hand side double
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator+=(double rhs);

        /*!
         * @brief Json long integer subtraction assignment operator
         * @param rhs Right hand side long integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator-=(long rhs);

        /*!
         * @brief Json integer subtraction assignment operator
         * @param rhs Right hand side integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator-=(int rhs);

        /*!
         * @brief Json double subtraction assignment operator
         * @param rhs Right hand side double
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator-=(double rhs);

        /*!
         * @brief Json long integer multiplication assignment operator
         * @param rhs Right hand side long integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator*=(long rhs);

        /*!
         * @brief Json integer multiplication assignment operator
         * @param rhs Right hand side integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator*=(int rhs);

        /*!
         * @brief Json double multiplication assignment operator
         * @param rhs Right hand side double
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator*=(double rhs);

        /*!
         * @brief Json long integer division assignment operator
         * @param rhs Right hand side long integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator/=(long rhs);

        /*!
         * @brief Json integer division assignment operator
         * @param rhs Right hand side integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator/=(int rhs);

        /*!
         * @brief Json double division assignment operator
         * @param rhs Right hand side double
         * @throw exceptions::InvalidOperator Throws when the Json object data is not numeric.
         * @return A reference to the Json object
         */
        Json & operator/=(double rhs);

        /*!
         * @brief Json long integer modulo assignment operator
         * @param rhs Right hand side long integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not a long integer.
         * @return A reference to the result Json object
         */
        Json & operator%=(long rhs);

        /*!
         * @brief Json integer modulo assignment operator
         * @param rhs Right hand side integer
         * @throw exceptions::InvalidOperator Throws when the Json object data is not a long integer.
         * @return A reference to the result Json object
         */
        Json & operator%=(int rhs);

        /*!
         * @brief Json size_t array subscript operator overload.
         * @throw exceptions::InvalidOperation Throws when Json object type is not Array.
         * @param index Item index.
         * @return A reference to item related to the given index.
         */
        Json & operator[](const size_t & index) const;

        /*!
         * @brief Json c-string array subscript operator overload.
         * @throw exceptions::InvalidOperation Throws when Json object type is not JsonObject.
         * @param key Item key
         * @return A reference to item related to the given key.
         */
        Json & operator[](const char * key) const;

        /*!
         * @brief Json JsonKey array subscript operator overload.
         * @throw exceptions::InvalidOperation Throws when Json object type is not JsonObject.
         * @param key Item key
         * @return A reference to item related to the given key.
         */
        Json & operator[](const JsonKey & key) const;

        /*!
         * @brief Json JsonPointer array subscript operator overload.
         * @throw exceptions::InvalidOperation Throws when Json object type is not iterable.
         * @param json_pointer A const reference to a JsonPointer object.
         * @return A reference to item related to the given JsonPointer object.
         */
        Json & operator[](const JsonPointer & json_pointer) const;

        /*!
         * @brief Json equality operator overload.
         * @param json_item A const reference to Json object that is going to get compared.
         * @return Boolean representing result of comparison.
         */
        bool operator==(const Json & json_item) const;

        /*!
         * @brief Json not-equal operator overload.
         * @param json_item A const reference to Json object that is going to get compared.
         * @return Boolean representing result of comparison.
         */
        bool operator!=(const Json & json_item) const;

        /*!
         * @brief Json pre-increment operator overload
         *
         * Increments double or long integer data within the Json object.
         * @throw exceptions::InvalidOperator Throws when Json object data is not float or long integer typed.
         * @return A reference to the Json object
         */
        Json & operator++();

        /*!
         * @brief Json post-increment operator overload
         *
         * Copies the Json object and increments float or long integer data within the copy.
         * @throw exceptions::InvalidOperator Throws when Json object data is not float or long integer typed.
         * @return A const Json object representing the original state of object(before incrementing).
         */
        const Json operator++(int);

        /*!
         * @brief Json pre-decrement operator overload
         *
         * Decrements float or long integer data within the Json object.
         * @throw exceptions::InvalidOperator Throws when Json object data is not float or long integer typed.
         * @return A reference to the Json object
         */
        Json & operator--();

        /*!
         * @brief Json post-decrement operator overload
         *
         * Copies the Json object and decrements float or long integer data within the copy.
         * @throw exceptions::InvalidOperator Throws when Json object data is not float or long integer typed.
         * @return A const Json object representing the original state of object(before decrementing).
         */
        const Json operator--(int);

        /*!
         * @brief Json long integer multiplication operator
         * @param rhs long integer that the Json object is going to be multiplied by.
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Multiplied Json object
         */
        Json operator*(long rhs);

        /*!
         * @brief Json int multiplication operator
         * @param rhs integer that the Json object is going to be multiplied by.
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Multiplied Json object
         */
        Json operator*(int rhs);


        /*!
         * @brief Json double multiplication operator
         * @param rhs double that the Json object is going to be multiplied by.
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Multiplied Json object
         */
        Json operator*(double rhs);

        /*!
         * @brief Json long integer addition operator
         * @param rhs long integer which is going to be added to Json
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of addition
         */
        Json operator+(long rhs);

        /*!
         * @brief Json integer addition operator
         * @param rhs integer which is going to be added to Json
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of addition
         */
        Json operator+(int rhs);

        /*!
         * @brief Json double addition operator
         * @param rhs double which is going to be added to Json
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of addition
         */
        Json operator+(double rhs);

        /*!
         * @brief Json long integer subtraction operator
         * @param rhs long integer which is going to get subtracted from Json object.
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of subtraction
         */
        Json operator-(long rhs);

        /*!
         * @brief Json integer subtraction operator
         * @param rhs integer which is going to get subtracted from Json object.
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of subtraction
         */
        Json operator-(int rhs);

        /*!
         * @brief Json double subtraction operator
         * @param rhs double which is going to get subtracted from Json object.
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of subtraction
         */
        Json operator-(double rhs);

        /*!
         * @brief Json long integer division operator
         * @param rhs Right hand side long integer
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of division operation
         */
        Json operator/(long rhs);

        /*!
         * @brief Json integer division operator
         * @param rhs Right hand side integer
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of division operation
         */
        Json operator/(int rhs);

        /*!
         * @brief Json double division operator
         * @param rhs Right hand side double
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of division operation
         */
        Json operator/(double rhs);

        /*!
         * @brief Json long integer modulo operator
         * @param rhs Right hand side long integer
         * @throw exceptions::InvalidOperator Throws when Json object data is not a long integer.
         * @return Json result of modulo operation
         */
        Json operator%(long rhs);

        /*!
         * @brief Json integer modulo operator
         * @param rhs Right hand side integer
         * @throw exceptions::InvalidOperator Throws when Json object data is not a integer.
         * @return Json result of modulo operation
         */
        Json operator%(int rhs);

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const Json & json_item);
        friend JsonObject;
        friend Array;
        friend JsonPatch;

        // Public Methods

        /*!
         * @brief Returns an iterator pointing to the beginning of Json object.
         *
         * This method returns an iterator object pointing the beginning of a Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created iterator object.
         */
        iterator begin();

        /*!
         * @brief Returns a iterator pointing to the past-the-end element in the Json object.
         *
         * This method returns an iterator object pointing to the past-the-end element of Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created iterator object.
         */
        iterator end();

        /*!
         * @brief Returns a const_iterator pointing to the beginning of the Json object.
         *
         * This public method returns a const_iterator pointing to the beginning of a Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created const_iterator object.
         */
        const_iterator cbegin() const;

        /*!
         * @brief Returns a const_iterator pointing to the past-the-end element in the Json object.
         *
         * This method returns and const_iterator object pointing to the past-the-end element in the Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created const_iterator object.
         */
        const_iterator cend() const;

        /*!
         * @brief Returns a reverse_iterator pointing to the beginning of Json object.
         *
         * This method returns an iterator object pointing the beginning of a Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created reverse_iterator object.
         */
        reverse_iterator rbegin();

        /*!
         * @brief Returns a reverse_iterator pointing to the past-the-end element in the Json object.
         *
         * This method returns an iterator object pointing to the past-the-end element of Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created reverse_iterator object.
         */
        reverse_iterator rend();

        /*!
         * @brief Returns a const_reverse_iterator pointing to the beginning of the Json object.
         *
         * This public method returns a const_reverse_iterator pointing to the beginning of a Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created const_reverse_iterator object.
         */
        const_reverse_iterator crbegin() const;

        /*!
         * @brief Returns a const_reverse_iterator pointing to the past-the-end element in the Json object.
         *
         * This method returns and const_reverse_iterator object pointing to the past-the-end element in the Json
         * object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created const_reverse_iterator object.
         */
        const_reverse_iterator crend() const;

        /*!
         * @brief Returns the JsonObject object stored withing Json object.
         * @return JsonObject stored inside the Json object.
         * @throw iterators::exceptions::InvalidType Throws when the Json object type is JsonObject.
         */
        JsonObject & items() const;

        /*!
         * @brief Applies a merge patch on Json object.
         * @param merge_patch A const reference to the merge patch Json object.
         */
        void merge_patch(const Json & merge_patch) noexcept;

        /*!
         * @brief Merges two Json objects.
         *
         * Creates a copy of current Json object and merges given Json object with the copy.
         * @param target A const reference to Json object which is about to be merged.
         * @return Merged Json object.
         */
        Json merge(const Json & target) const;

        /*!
         * @brief Returns Json object at given size_t index.
         *
         * This method also provides bound checking of the Array object.
         * @param index size_t index
         * @throw exceptions::InvalidOperation Throws when the Json object is not Array type.
         * @return Json object at the given index.
         */
        Json & at(size_t index) const;

        /*!
         * @brief Returns Json object at given std::string key.
         * @param key std::string key related to Json object in a JsonObject object.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not JsonObject.
         * @return Json object at the given std::string key.
         */
        Json & at(const std::string & key) const;

        /*!
         * @brief Returns Json object at the given JsonPointer address.
         * @param json_pointer A const reference to the JsonPointer object.
         * @throw exceptions::InvalidOperation Throws when the Json object is not iterable type.
         * @return Json object at the given JsonPointer address.
         */
        Json & at(const JsonPointer & json_pointer) const;

        /*!
         * @brief Returns Json object related to given JsonKey key.
         * @param key A const reference to JsonKey object.
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return Json object related to the given JsonKey key.
         */
        Json & at(const JsonKey & key) const;

        /*!
         * @brief Gets a value related to a key or returns specified value as a default.
         * @param key JsonKey key which the method is going to look for.
         * @param default_return Default value which will be returned in case of the key not existing.
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return A Json object whether it's the value related to the key or a copy of default value.
         */
        Json get(const JsonKey & key, const Json & default_return) const;

        /*!
         * @brief Gets a value related to a key or returns specified value as a default.
         * @param key The ke which the method is going to look for.
         * @param default_return Default value which will be returned in  case of the key not existing.
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return A Json object whether it's the value related to the key or the default value.
         */
        Json get(const JsonKey & key, Json && default_return) const;

        /*!
         * @brief Gets a value related to a key or returns specified value as a default.
         * @param key The key which the method is going to look for.
         * @param default_return Default value which will be returned in case of the key not existing.
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return A Json object whether it's the value related to the key or a copy of default value.
         */
        Json get(const std::string & key, const Json & default_return) const;

        /*!
         * @brief Gets a value related to a key or returns specified value as a default.
         * @param key The key which the method is going to look for.
         * @param default_return Default value which will be returned in case of the key not existing.
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return A Json object whether it's the value related to the key or the default value.
         */
        Json get(const std::string & key, Json && default_return) const;

        /*!
         * @brief Returns a const_iterator pointing to the Json object at the given index.
         * @param index Json object index
         * @throw exceptions::InvalidOperation Throws when the Json object is not Array type.
         * @return Created const_iterator object.
         */
        const_iterator get_item(long index) const;

        /*!
         * @brief Creates a JsonPatch to the given destination Json object.
         *
         * This public method creates an JsonPatch based on current Json object and the const reference to destination
         * Json object. It uses the current Json object as the source of JsonPatch.
         * @param dst A const reference to the destination of JsonPatch.
         * @return Created JsonPatch object which transforms the current Json object into the dst.
         */
        JsonPatch get_diff(const Json & dst) const;

        /*!
         * @brief Erases the Json object at the given index.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not Array.
         * @param index Json object index
         */
        void erase(long index);

        /*!
         * @brief Erases the Json object related to the given key.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not JsonObject.
         * @param key std::string key
         */
        void erase(const std::string & key);

        /*!
         * @brief Erases the Json object related to the given key.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not JsonObject.
         * @param key A const reference to a JsonKey object.
         */
        void erase(const JsonKey & key);

        /*!
         * @brief Erases the Json object at the given JsonPointer address.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not iterable.
         * @param json_pointer A const reference to a JsonPointer object.
         */
        void erase(const JsonPointer & json_pointer);

        /*!
         * @brief Pushes a new item into the Array inside Json object.
         * @throw exceptions::InvalidOperation Throws when the Json object is not an Array.
         * @param new_item A const reference to the the new Json object.
         */
        void push_back(const Json & new_item);

        /*!
         * @brief Moves a new Json object into the Array inside Json object.
         * @throw exceptions:;InvalidOperation Throws when the Json object is not an Array.
         * @param new_item A r-value reference to the Json object which is about to be moved.
         */
        void push_back(Json && new_item);

        /*!
         * @brief Inserts a new std::pair into the JsonObject stored inside Json object.
         * @throw exceptions::InvalidOperation Throws when the Json object is not a JsonObject.
         * @param new_item A const reference to the new std::pair object.
         */
        void insert(const pair_type & new_item);

        /*!
         * @brief Moves a new std::pair into the JsonObject stored inside Json object.
         * @throw exceptions::InvalidOperation Throws when the Json object is not a JsonObject.
         * @param new_item A r-value reference to the std::pair object which is about to be moved.
         */
        void insert(pair_type && new_item);

        /*!
         * @brief Inserts a new item to into the Array at the given position.
         * @param position A const reference to a const_iterator object pointing to the intended position.
         * @param item A const reference to the Json item about to get inserted into the Array.
         */
        void insert(const const_iterator & position, const Json & item);

        /*!
         * @brief Moves a new item to into the Array at the given position.
         * @param position A const reference to a const_iterator object pointing to the intended position.
         * @param item A r-value reference to the Json item about to get moved into the Array.
         */
        void insert(const const_iterator & position, Json && item);

        /*!
         * @brief Returns the last element in the Array.
         * @throw exceptions::InvalidOperation Throws when the Json object is not an Array.
         * @return A reference to the last element in the Array.
         */
        Json & back() const noexcept;

        /*!
         * @brief Returns the inner type of Json object.
         * @return DataType of the object stored inside Json object.
         */
        inline DataType type() const noexcept {return used_type;}

        /*!
         * @brief Checks if the Json object is an empty container.
         * @throw exceptions::InvalidOperation Throws when the Json object is not a container(iterable type).
         * @return Boolean representing the result of the checking.
         */
        bool empty() const;

        /*!
         * @brief Serializes the Json object.
         * @return Serialized std::string of Json object.
         */
        std::string serialize() const;

        /*!
         * @brief Counts how many instances of given object exist in the Array.
         * @param item A const reference to object that is going to be counted.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not Array.
         * @return size_t count of same objects found.
         */
        size_t count(const Json & item) const;

        /*!
         * @brief Checks is the given key exists in JsonObject.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not JsonObject.
         * @param key A const reference to the JsonKey
         * @return Result of the checking.
         */
        bool contains(const JsonKey & key) const;

        /*!
         * @brief Checks is the given Json item exists in the container.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not iterable.
         * @param item Const reference to the target Json item
         * @return Result of the checking
         */
        bool contains(const Json & item) const;

        /*!
         * @brief Returns an iterator to the Json object related to given JsonKey.
         * @param key A const reference to JsonKey object.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not JsonObject.
         * @return iterator pointing to the object related to the given JsonKey. If the given key is not found
         * this->end() would be returned instead.
         */
        iterator find(const JsonKey & key);

        /*!
         * @brief Returns an iterator to the given Json in the container.
         * @param item A const reference to Json object.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not iterable(container).
         * @return iterator pointing to the found object inside Json container. If the Json object is not found
         * this->end() would be returned instead.
         */
        iterator find(const Json & item);

        /*!
         * @brief Returns a const_iterator to the Json object related to given JsonKey.
         * @param key A const reference to JsonKey object.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not JsonObject.
         * @return const_iterator pointing to the object related to the given JsonKey. If the given key is not found
         * this->cend() would be returned instead.
         */
        const_iterator find(const JsonKey & key) const;

        /*!
         * @brief Returns a const_iterator to the given Json in the container.
         * @param item A const reference to Json object.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not iterable(container).
         * @return const_iterator pointing to the found object inside Json container. If the Json object is not found
         * this->cend() would be returned instead.
         */
        const_iterator find(const Json & item) const;

        /*!
         * @brief Returns an iterator to the item that passed the given test function.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not Array.
         * @param test_func A const reference to test function object.
         * @return An iterator pointing to the first item that passed the test or this->end() if none of them passed it.
         */
        iterator find_if(const std::function<bool(const Json &)> & test_func);

        /*!
         * @brief Returns a const_iterator to the item that passed the given test function.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not Array.
         * @param test_func A const reference to test function object.
         * @return A const_iterator pointing to the first item that passed the test or this->cend() if none of
         * them passed it.
         */
        const_iterator find_if(const std::function<bool(const Json &)> & test_func) const;

        /*!
         * @brief Returns an iterator to the item that passed the given test function.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not JsonObject.
         * @param test_func A const reference to test function object.
         * @return An iterator pointing to the first item that passed the test or this->end() if none of them passed it.
         */
        iterator find_if(const std::function<bool(const pair_type &)> & test_func);

        /*!
         * @brief Returns a const_iterator to the item that passed the given test function.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not JsonObject.
         * @param test_func A const reference to test function object.
         * @return A const_iterator pointing to the first item that passed the test or this->cend() if none of
         * them passed it.
         */
        const_iterator find_if(const std::function<bool(const pair_type &)> & test_func) const;

        /*!
         * @brief Returns the index of given Json object inside Array.
         * @param item A const reference to the Json object that is going to be checked inside the Array.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not Array.
         * @return size_t index of given Json object inside the Array.
         */
        size_t find_index(const Json & item) const;

        /*!
         * @brief Returns the index of Json object related to the given const_iterator inside Array.
         * @param it A const reference to the const_iterator that is going to be checked inside the Array.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not Array.
         * @return size_t index of Json object related to the given const_iterator inside the Array.
         */
        size_t find_index(const const_iterator & it) const;

        /*!
         * @brief Returns the size of the container stored inside Json object.
         *
         * If the data type is not a container 1 will be returned as size.
         * If the data type is not unknown then a 0 will be returned.
         * @return size_t size of the Json object.
         */
        size_t size() const noexcept;

        /*!
         * @brief Updates the JsonObject with the given Json object.
         *
         * This public method replaces all the JsonObject keys existing inside the given Json object with it's
         * JsonObject values. If a key doesn't exist in the given Json object then it will remain untouched. Any
         * new key will be added with it's corresponding value inside the given JsonObject.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not JsonObject.
         * @param target A const reference to Json which is going to update stored JsonObject.
         */
        void update(const Json & target);

        /*!
         * @brief int data getter
         * @return A reference to int data stored inside
         */
        long & get_int();

        /*!
         * @brief double data getter
         * @return A reference to double data stored inside
         */
        double & get_double();

        /*!
         * @brief bool data getter
         * @return A reference to bool data stored inside
         */
        bool & get_bool();

        /*!
         * @brief std::string data getter
         * @return A reference to std::string data stored inside
         */
        std::string & get_string();

        /*!
         * @brief Array data getter
         * @return A reference to Array data stored inside
         */
        Array & get_array();

        /*!
         * @brief JsonObject data getter
         * @return A reference to JsonObject data stored inside
         */
        JsonObject & get_json_object();

        /*!
         * @brief Finds the given Json object in the given range.
         * @tparam T Type of given iterators.
         * @param first First iterator in the range.
         * @param last Last iterator in the range.
         * @param item A const reference to the Json object going to be searched.
         * @throw iterators::exceptions::InvalidIteration Throws when the iterator is not an Array iterator.
         * @return The iterator with the given type pointing to the given item in the container. If the item
         * does not exist in the range iterator pointing to this->end() will be returned instead.
         */
        template<typename T>
        T find_in_range(const T & first, const T & last, const Json & item) const {
            first.check_type(IteratorTypes::array_iterator_type);
            last.check_type(IteratorTypes::array_iterator_type);
            return T{std::find(*first.array_iterator, *last.array_iterator, item)};
        }

        /*!
         * @brief Counts the instances of the given Json object in the given range.
         * @tparam T Type of given iterators.
         * @param first First iterator in the range.
         * @param last Last iterator in the range.
         * @param item A const reference to the Json object that is going to be searched.
         * @throw iterators::exceptions::InvalidIteration Throws when the iterator is not an Array iterator.
         * @return size_t count of instances of the given Json object in the container.
         */
        template<typename T>
        size_t count_in_range(const T & first, const T & last, const Json & item) const {
            first.check_type(IteratorTypes::array_iterator_type);
            last.check_type(IteratorTypes::array_iterator_type);
            return std::count(* first.array_iterator, * last.array_iterator, item);
        }

        // Destructors
        /*!
         * @brief Json destructor
         *
         * Deletes data stored within a Json object.
         */
        ~Json();
    };

    /*!
     * @brief Json stream insertion operator overload.
     *
     * Serializes the Json object and inserts it into the given output stream.
     * @param os [out] Output Stream
     * @param json_item A const reference to Json object which is about to get serialized.
     * @return
     */
    std::ostream & operator<<(std::ostream & os, const Json & json_item);
}

#endif
