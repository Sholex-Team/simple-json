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
#include "exceptions/iterator_exceptions.h"
#include <utility>
#include "exceptions/invalid_operator.h"
#include "../json_utils.h"
#include "json_pointer.h"
#include <algorithm>
#include <functional>
#include "exceptions/invalid_merge.h"

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
        void check_type(const DataType target_type) const;
        inline void can_iterate() const {
            if (!(used_type == DataType::array_type || used_type == DataType::json_object_type)) {
                throw exceptions::InvalidOperation {};
            }
        }
        void clean_memory() noexcept;
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
            void add_to_iterator() override;
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
             * This operator copies the iterator object and advances the original iterator by one position.
             * @return A const copy of iterator object before advancing.
             */
            const iterator operator++(int);

            /*!
             * @brief iterator pre-increment operator overload.
             *
             * This operator advances the iterator by one position.
             * @return A reference to advanced operator.
             */
            iterator & operator++();

            /*!
             * @brief iterator addition operator overload.
             *
             * This operator copies the iterator object and advances the copy by specified positions.
             * @param i Positions that the iterator is going to advance.
             * @return Advanced iterator object.
             */
            iterator operator+(size_t i) const;

            /*!
             * @brief iterator subtraction operator overload.
             *
             * This operator copies the iterator object and moves back the copy by given positions.
             * @param i Positions that the iterator is going to move back.
             * @return Moved back iterator object.
             */
            iterator operator-(size_t i) const;

            /*!
             * @brief iterator addition assignment operator overload.
             *
             * This operator advances the iterator by given positions.
             * @param i Positions that the iterator is going to advance.
             * @return Advanced iterator.
             */
            iterator & operator+=(size_t i);

            /*!
             * @brief iteration subtraction assignment operator overload.
             *
             * This operator moves the iterator back by given positions.
             * @param i Positions that the iterator it going to move back.
             * @return Moved back iterator.
             */
            iterator & operator-=(size_t i);

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
            void add_to_iterator() override;
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

            // Operators
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
             * Copies the const_iterator and advances the original const_iterator object and returns the copy.
             * @return A copied const_iterator object of the original one before advancing.
             */
            const_iterator operator++(int);

            /*!
             * @brief const_iterator pre-increment operator overload.
             *
             * Advances the const_iterator object by one position.
             * @return A reference to advanced const_iterator object.
             */
            const_iterator & operator++();

            /*!
             * @brief const_iterator addition operator.
             *
             * Copies the const_iterator and advances the copy by given positions.
             * @param i Positions that the copied const_iterator object is going to advance.
             * @return Advanced copy of const_iterator object.
             */
            const_iterator operator+(size_t i) const;

            /*!
             * @brief const_iterator subtraction operator.
             *
             * Copies the const_iterator object and moves the copy back by given positions.
             * @param i Positions that the copied const_iterator object is going to move back.
             * @return Moved back copy of const_iterator object.
             */
            const_iterator operator-(size_t i) const;

            /*!
             * @brief const_iterator addition assignment operator overload.
             *
             * Advances the const_iterator object by given positions.
             * @param i Positions and the const_iterator object is going to advance.
             * @return A reference to advanced const_iterator object.
             */
            const_iterator & operator+=(size_t i);

            /*!
             * @brief const_iterator subtractions assignment operator overload.
             *
             * Moves the const_iterator object back by given positions.
             * @param i Positions that the const_iterator object to going to move back.
             * @return A reference to moved back const_iterator object.
             */
            const_iterator & operator-=(size_t i);

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
         * @brief Returns a const_Iterator pointing to the past-the-end element in the Json object.
         *
         * This method returns and const_iterator object pointing to the past-the-end element in the Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created const_iterator object.
         */
        const_iterator cend() const;

        /*!
         * @brief Returns the JsonObject object stored withing Json object.
         * @return JsonObject stored inside the Json object.
         * @throw iterators::exceptions::InvalidType Throws when the Json object type is JsonObject.
         */
        JsonObject & items() const;

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
        explicit operator const char *() const;

        // Assignment Operator Overloading
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
         * Assigns a JsonObject to the the current Json object using given initializer_list
         * @param initializer_list JsonObject initializer_list containing items inside a JsonObject.
         * @return A reference to modified Json object.
         */
        Json & operator=(const json_list_type & initializer_list);

        /*!
         * @brief Json Array initializer_list assignment operator overload.
         *
         * Assigns a Array to the the current Json object using given initializer_list
         * @param json_object_list Array initializer_list containing items inside a JsonObject.
         * @return A reference to modified Json object.
         */
        Json & operator=(const array_list_type & array_list);

        /*!
         * @brief Json DataType assignment operator overload.
         *
         * Creates an empty Json object with given DataType and assigns it to the current Json object.
         * @param object_type A reference to modified Json object.
         * @return
         */
        Json & operator=(DataType object_type);

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const Json & json_item);
        friend JsonObject;
        friend Array;
        friend JsonPatch;

        // Array Subscript Operator overloading
        Json & operator[](const size_t & index) const;
        Json & operator[](const char * & index) const;
        Json & operator[](const JsonKey & index) const;
        Json & operator[](const JsonPointer & json_pointer) const;

        // Comparison
        bool operator==(const Json & json_item) const;
        bool operator!=(const Json & json_item) const;

        // Public Method
        void merge_patch(const Json & merge_patch) noexcept;
        Json merge(const Json & target) const;
        Json & at(size_t) const;
        Json & at(const std::string &) const;
        Json & at(const JsonPointer &) const;
        Json & at(const JsonKey &) const;
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
