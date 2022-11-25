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
#include <variant>

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
        std::variant<std::monostate, long int, double, bool, Array *, std::string *, JsonObject *> data;

        // Private Methods
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
         * @brief Json Iterator class
         */
         using iterator = iterators::JsonIterator<Array::iterator, JsonObject::iterator, Json>;

        /*!
         * @brief Json Const Iterator class
         */
        using const_iterator = iterators::JsonIterator<Array::const_iterator, JsonObject::const_iterator, const Json>;

        /*!
         * @brief Json Reverse Iterator class
         */
         using reverse_iterator = iterators::JsonIterator<Array::reverse_iterator, JsonObject::reverse_iterator, Json>;


        /*!
         * @brief Json Const Reverse Iterator class
         */
         using const_reverse_iterator = iterators::JsonIterator<
                 Array::const_reverse_iterator, JsonObject::const_reverse_iterator, const Json
         >;

        // Constructors
        /*!
         * @brief Json default constructor.
         *
         * Creates a Json object with an empty JsonObject within.
         */
        [[nodiscard]] Json();

        /*!
         * @brief Json double data type constructor
         * @param data double data
         */
        [[nodiscard]] Json(double data);

        /*!
         * @brief Json long int data type constructor
         * @param data long int data
         */
        [[nodiscard]] Json(long int data);

        /*!
         * @brief Json bool data type constructor
         * @param data bool data
         */
        [[nodiscard]] Json(bool data);

        /*!
         * @brief Json int data type constructor
         * @param data int data
         */
        [[nodiscard]] Json(int data);

        /*!
         * @brief Json null constructor
         * @param data std::nullptr_t data
         */
        [[nodiscard]] Json(std::nullptr_t data);

        /*!
         * @brief Json Array constructor
         * @param data Const reference to Array data
         */
        [[nodiscard]] explicit Json(const Array & data);

        /*!
         * @brief Json Array constructor.
         * @param data A r-value reference to Array data
         */
        [[nodiscard]] Json(Array && data);

        /*!
         * @brief Json Array initializer_list constructor
         * @param initializer_list A const reference to an Array initializer-List data
         */
        [[nodiscard]] Json(const array_list_type & initializer_list);

        /*!
         * @brief Json std::string constructor
         * @param data A const reference to std::string data
         */
        [[nodiscard]] Json(const std::string & data);

        /*!
         * @brief Json std::string constructor
         * @param data A r-value reference to std::string data
         */
        [[nodiscard]] Json(std::string && data);

        /*!
         * @brief Json c-string constructor
         * @param data const char pointer pointing to the first character of c-string
         */
        [[nodiscard]] Json(const char * data);

        /*!
         * @brief Json JsonObject constructor
         * @param data A const reference to JsonObject data
         */
        [[nodiscard]] explicit Json(const JsonObject & data);

        /*!
         * @brief Json JsonObject constructor
         * @param data A r-value reference to JsonObject data
         */
        [[nodiscard]] Json(JsonObject && data);

        /*!
         * @brief Json JsonObject initializer_list constructor
         * @param initializer_list A const reference to JsonObject initializer_list
         */
        [[nodiscard]] Json(const json_list_type & initializer_list);

        /*!
         * @brief Json copy constructor
         * @param json_item A reference to Json object which is about to get copied
         */
        [[nodiscard]] Json(const Json & json_item);

        /*!
         * @brief Json move constructor
         * @param json_item A r-value reference to Json which is about to be moved
         */
        [[nodiscard]] Json(Json && json_item) noexcept;

        /*!
         * @brief Json data type constructor
         *
         * Creates a new empty Json object based on the given data type
         * @param object_type Data type which is about to be used to create an empty Json object
         */
        [[nodiscard]] explicit Json(DataType object_type);

        // Explicit conversion operators
        /*!
         * @brief Json to long int conversion operator
         * @return int data
         */
        [[nodiscard]] explicit operator long int() const;

        /*!
         * @brief Json to double conversion operator
         * @return double data
         */
        [[nodiscard]] explicit operator double() const;

        /*!
         * @brief Json to Array conversion operator
         * @return Array data
         */
        [[nodiscard]] explicit operator Array() const;

        /*!
         * @brief Json to std::string conversion operator
         * @return std::string data
         */
        [[nodiscard]] explicit operator std::string() const;

        /*!
         * @brief Json to JsonObject conversion operator
         * @return JsonObject data
         */
        [[nodiscard]] explicit operator JsonObject() const;

        /*!
         * @brief Json to const c-string conversion operator
         * @return Const pointer to first character of c-string data
         */
        [[nodiscard]] explicit operator const char * () const;

        // Operator Overloading
        /*!
         * @brief Json copy assignment operator overload
         * @param data A const reference to Json object which is about to get copied
         * @return A reference to modified Json object.
         */
        Json & operator=(const Json & data);

        /*!
         * @brief Json move assignment operator overload
         * @param data A r-value reference to Json object which is about ot be moved
         * @return A reference to modified Json object
         */
        Json & operator=(Json && data) noexcept;

        /*!
         * @brief Json JsonObject initializer_list assignment operator overload.
         *
         * Assigns a JsonObject to the the current Json object using given initializer_list.
         * @param initializer_list JsonObject initializer_list containing items inside a JsonObject
         * @return A reference to modified Json object
         */
        Json & operator=(const json_list_type & initializer_list);

        /*!
         * @brief Json Array initializer_list assignment operator overload.
         *
         * Assigns a Array to the the current Json object using given initializer_list.
         * @param initializer_list Array initializer_list containing items inside a JsonObject
         * @return A reference to modified Json object
         */
        Json & operator=(const array_list_type & initializer_list);

        /*!
         * @brief Json DataType assignment operator overload.
         *
         * Creates an empty Json object with given DataType and assigns it to the current Json object
         * @param object_type A reference to modified Json object
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
         * @brief Json size_t array subscript operator overload
         * @throw exceptions::InvalidOperation Throws when Json object type is not Array.
         * @param index Item index.
         * @return A reference to item related to the given index
         */
        [[nodiscard]] Json & operator[](const size_t & index) const;

        /*!
         * @brief Json c-string array subscript operator overload
         * @throw exceptions::InvalidOperation Throws when Json object type is not JsonObject.
         * @param key Item key
         * @return A reference to item related to the given key
         */
        [[nodiscard]] Json & operator[](const char * key) const;

        /*!
         * @brief Json JsonKey array subscript operator overload
         * @throw exceptions::InvalidOperation Throws when Json object type is not JsonObject.
         * @param key Item key
         * @return A reference to item related to the given key
         */
        [[nodiscard]] Json & operator[](const JsonKey & key) const;

        /*!
         * @brief Json JsonPointer array subscript operator overload
         * @throw exceptions::InvalidOperation Throws when Json object type is not iterable.
         * @param json_pointer A const reference to a JsonPointer object
         * @return A reference to item related to the given JsonPointer object
         */
        [[nodiscard]] Json & operator[](const JsonPointer & json_pointer) const;

        /*!
         * @brief Json equality operator overload
         * @param json_item A const reference to Json object that is going to get compared
         * @return Boolean representing result of comparison
         */
        [[nodiscard]] bool operator==(const Json & json_item) const;

        /*!
         * @brief Json not-equal operator overload
         * @param json_item A const reference to Json object that is going to get compared
         * @return Boolean representing result of comparison
         */
        [[nodiscard]] bool operator!=(const Json & json_item) const;

        /*!
         * @brief Json pre-increment operator overload
         * @throw exceptions::InvalidOperator Throws when Json object data is not float or long integer typed.
         * @return A reference to the Json object
         */
        Json & operator++();

        /*!
         * @brief Json post-increment operator overload
         * @throw exceptions::InvalidOperator Throws when Json object data is not float or long integer typed.
         * @return A const Json object representing the original state of object(before incrementing).
         */
        const Json operator++(int);

        /*!
         * @brief Json pre-decrement operator overload
         * @throw exceptions::InvalidOperator Throws when Json object data is not float or long integer typed.
         * @return A reference to the Json object
         */
        [[nodiscard]] Json & operator--();

        /*!
         * @brief Json post-decrement operator overload
         * @throw exceptions::InvalidOperator Throws when Json object data is not float or long integer typed.
         * @return A const Json object representing the original state of object(before decrementing).
         */
        [[nodiscard]] const Json operator--(int);

        /*!
         * @brief Json long integer multiplication operator
         * @param rhs long integer that the Json object is going to be multiplied by
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Multiplied Json object
         */
        [[nodiscard]] Json operator*(long rhs);

        /*!
         * @brief Json int multiplication operator
         * @param rhs integer that the Json object is going to be multiplied by
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Multiplied Json object
         */
        [[nodiscard]] Json operator*(int rhs);


        /*!
         * @brief Json double multiplication operator
         * @param rhs double that the Json object is going to be multiplied by
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Multiplied Json object
         */
        [[nodiscard]] Json operator*(double rhs);

        /*!
         * @brief Json long integer addition operator
         * @param rhs long integer which is going to be added to Json
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of addition
         */
        [[nodiscard]] Json operator+(long rhs);

        /*!
         * @brief Json integer addition operator
         * @param rhs integer which is going to be added to Json
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of addition
         */
        [[nodiscard]] Json operator+(int rhs);

        /*!
         * @brief Json double addition operator
         * @param rhs double which is going to be added to Json
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of addition
         */
        [[nodiscard]] Json operator+(double rhs);

        /*!
         * @brief Json long integer subtraction operator
         * @param rhs long integer which is going to get subtracted from Json object
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of subtraction
         */
        [[nodiscard]] Json operator-(long rhs);

        /*!
         * @brief Json integer subtraction operator
         * @param rhs integer which is going to get subtracted from Json object
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of subtraction
         */
        [[nodiscard]] Json operator-(int rhs);

        /*!
         * @brief Json double subtraction operator
         * @param rhs double which is going to get subtracted from Json object
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of subtraction
         */
        [[nodiscard]] Json operator-(double rhs);

        /*!
         * @brief Json long integer division operator
         * @param rhs Right hand side long integer
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of division operation
         */
        [[nodiscard]] Json operator/(long rhs);

        /*!
         * @brief Json integer division operator
         * @param rhs Right hand side integer
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of division operation
         */
        [[nodiscard]] Json operator/(int rhs);

        /*!
         * @brief Json double division operator
         * @param rhs Right hand side double
         * @throw exceptions::InvalidOperator Throws when Json object data is not numeric.
         * @return Json result of division operation
         */
        [[nodiscard]] Json operator/(double rhs);

        /*!
         * @brief Json long integer modulo operator
         * @param rhs Right hand side long integer
         * @throw exceptions::InvalidOperator Throws when Json object data is not a long integer.
         * @return Json result of modulo operation
         */
        [[nodiscard]] Json operator%(long rhs);

        /*!
         * @brief Json integer modulo operator
         * @param rhs Right hand side integer
         * @throw exceptions::InvalidOperator Throws when Json object data is not a integer.
         * @return Json result of modulo operation
         */
        [[nodiscard]] Json operator%(int rhs);

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const Json & json_item);
        friend class JsonObject;
        friend class Array;
        friend class JsonPatch;

        // Public Methods

        /*!
         * @brief Returns an iterator pointing to the beginning of Json object.
         *
         * This method returns an iterator object pointing the beginning of a Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created iterator object
         */
        [[nodiscard]] iterator begin();

        /*!
         * @brief Returns a iterator pointing to the past-the-end element in the Json object.
         *
         * This method returns an iterator object pointing to the past-the-end element of Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created iterator object
         */
        [[nodiscard]] iterator end();

        /*!
         * @brief Returns a const_iterator pointing to the beginning of the Json object.
         *
         * This public method returns a const_iterator pointing to the beginning of a Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created const_iterator object
         */
        [[nodiscard]] const_iterator cbegin() const;

        /*!
         * @brief Returns a const_iterator pointing to the past-the-end element in the Json object.
         *
         * This method returns and const_iterator object pointing to the past-the-end element in the Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created const_iterator object
         */
        [[nodiscard]] const_iterator cend() const;

        /*!
         * @brief Returns a reverse_iterator pointing to the beginning of the reversed Json object.
         *
         * This method returns an iterator object pointing the beginning of the reversed Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created reverse_iterator object
         */
        [[nodiscard]] reverse_iterator rbegin();

        /*!
         * @brief Returns a reverse_iterator pointing to the past-the-end element in the reversed Json object.
         *
         * This method returns an iterator object pointing to the past-the-end element of the reversed Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created reverse_iterator object
         */
        [[nodiscard]] reverse_iterator rend();

        /*!
         * @brief Returns a const_reverse_iterator pointing to the beginning of the reversed Json object.
         *
         * This public method returns a const_reverse_iterator pointing to the beginning of the reversed Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created const_reverse_iterator object
         */
        [[nodiscard]] const_reverse_iterator crbegin() const;

        /*!
         * @brief Returns a const_reverse_iterator pointing to the past-the-end element in the reversed Json object.
         *
         * This method returns and const_reverse_iterator object pointing to the past-the-end element in the reversed
         * Json object.
         * The Json object must be an Array or JsonObject type.
         * @throw iterators::exceptions::InvalidIteration Throws when data type of Json object is not iterable.
         * @return Created const_reverse_iterator object.
         */
        [[nodiscard]] const_reverse_iterator crend() const;

        /*!
         * @brief Returns the JsonObject object stored withing Json object.
         * @throw iterators::exceptions::InvalidType Throws when the Json object type is JsonObject.
         * @return JsonObject stored inside the Json object
         */
        [[nodiscard]] JsonObject & items() const;

        /*!
         * @brief Applies a merge patch on Json object.
         * @param merge_patch A const reference to the merge patch Json object
         */
        void merge_patch(const Json & merge_patch) noexcept;

        /*!
         * @brief Merges two Json objects.
         *
         * Creates a copy of current Json object and merges given Json object with the copy.
         * @param target A const reference to Json object which is about to be merged
         * @return Merged Json object
         */
        [[nodiscard]] Json merge(const Json & target) const;

        /*!
         * @brief Returns Json object at given size_t index
         *
         * This method also provides bound checking of the Array object.
         * @param index size_t index
         * @throw exceptions::InvalidOperation Throws when the Json object is not Array type.
         * @return Json object at the given index
         */
        [[nodiscard]] Json & at(size_t index) const;

        /*!
         * @brief Returns Json object at given std::string key.
         * @param key std::string key pointing to a Json object in the JsonObject object.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not JsonObject.
         * @return Json object at the given std::string key
         */
        [[nodiscard]] Json & at(const std::string & key) const;

        /*!
         * @brief Returns Json object at the given JsonPointer address.
         * @param json_pointer A const reference to the JsonPointer object
         * @throw exceptions::InvalidOperation Throws when the Json object is not iterable type.
         * @return Json object at the given JsonPointer address
         */
        [[nodiscard]] Json & at(const JsonPointer & json_pointer) const;

        /*!
         * @brief Returns Json object related to given JsonKey key.
         * @param key A const reference to JsonKey object
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return Json object related to the given JsonKey key
         */
        [[nodiscard]] Json & at(const JsonKey & key) const;

        /*!
         * @brief Gets a value related to a key or returns specified value as a default.
         * @param key JsonKey key which the method is going to look for
         * @param default_return Default value which will be returned in case of the key not existing
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return A Json object whether it's the value related to the key or a copy of default value.
         */
        [[nodiscard]] Json get(const JsonKey & key, const Json & default_return) const;

        /*!
         * @brief Gets a value related to a key or returns specified value as a default.
         * @param key The key which the method is going to look for
         * @param default_return Default value which will be returned in case of key not existing
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return A Json object whether it's the value related to the key or the default value.
         */
        [[nodiscard]] Json get(const JsonKey & key, Json && default_return) const;

        /*!
         * @brief Gets a value related to a key or returns specified value as a default.
         * @param key The key which the method is going to look for
         * @param default_return Default value which will be returned in case of the key not existing
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return A Json object whether it's the value related to the key or a copy of default value.
         */
        [[nodiscard]] Json get(const std::string & key, const Json & default_return) const;

        /*!
         * @brief Gets a value related to a key or returns specified value as a default.
         * @param key The key which the method is going to look for
         * @param default_return Default value which will be returned in case of the key not existing
         * @throw exceptions::InvalidOperation Throws when the Json object is not JsonObject typed.
         * @return A Json object whether it's the value related to the key or the default value.
         */
        [[nodiscard]] Json get(const std::string & key, Json && default_return) const;

        /*!
         * @brief Returns a const_iterator pointing to the Json object at the given index.
         * @param index Json object index
         * @throw exceptions::InvalidOperation Throws when the Json object is not Array type.
         * @return Created const_iterator object
         */
        [[nodiscard]] const_iterator get_item(long index) const;

        /*!
         * @brief Creates a JsonPatch to the given destination Json object.
         *
         * This public method creates a JsonPatch based on current Json object and the const reference to destination
         * Json object differences. It uses the current Json object as the source of JsonPatch.
         * @param dst A const reference to the destination of JsonPatch
         * @return Created JsonPatch object which transforms the current Json object into the dst.
         */
        [[nodiscard]] JsonPatch get_diff(const Json & dst) const;

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
         * @param key A const reference to a JsonKey object
         */
        void erase(const JsonKey & key);

        /*!
         * @brief Erases the Json object at the given JsonPointer address.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not iterable.
         * @param json_pointer A const reference to a JsonPointer object
         */
        void erase(const JsonPointer & json_pointer);

        /*!
         * @brief Pushes a new item into the Array inside Json object.
         * @throw exceptions::InvalidOperation Throws when the Json object is not an Array.
         * @param new_item A const reference to the the new Json object
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
         * @param new_item A const reference to the new std::pair object
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
         * @return A reference to the last element in the Array
         */
        [[nodiscard]] Json & back() const noexcept;

        /*!
         * @brief Returns the inner type of Json object.
         * @return DataType of the object stored inside Json object
         */
        [[nodiscard]] inline DataType type() const noexcept {return used_type;}

        /*!
         * @brief Checks if the Json object is an empty container.
         * @throw exceptions::InvalidOperation Throws when the Json object is not a container(iterable type).
         * @return Boolean representing the result of the checking
         */
        [[nodiscard]] bool empty() const;

        /*!
         * @brief Serializes the Json object.
         * @return Serialized std::string of Json object
         */
        [[nodiscard]] std::string serialize() const;

        /*!
         * @brief Counts how many instances of given object exist in the Array.
         * @param item A const reference to object that is going to be counted
         * @throw exceptions::InvalidOperation Throws when the Json object type is not Array.
         * @return size_t count of same objects found
         */
        [[nodiscard]] size_t count(const Json & item) const;

        /*!
         * @brief Checks is the given key exists in JsonObject.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not JsonObject.
         * @param key A const reference to the JsonKey
         * @return Result of the checking
         */
        [[nodiscard]] bool contains(const JsonKey & key) const;

        /*!
         * @brief Checks is the given Json item exists in the container.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not iterable.
         * @param item Const reference to the target Json item
         * @return Result of the checking
         */
        [[nodiscard]] bool contains(const Json & item) const;

        /*!
         * @brief Returns an iterator to the Json object related to given JsonKey.
         * @param key A const reference to JsonKey object
         * @throw exceptions::InvalidOperation Throws when the Json object type is not JsonObject.
         * @return iterator pointing to the object related to the given JsonKey. If the given key is not found
         * this->end() would be returned instead.
         */
        [[nodiscard]] iterator find(const JsonKey & key);

        /*!
         * @brief Returns an iterator to the given Json in the container.
         * @param item A const reference to Json object
         * @throw exceptions::InvalidOperation Throws when the Json object type is not iterable(container).
         * @return iterator pointing to the found object inside Json container. If the Json object is not found
         * this->end() would be returned instead.
         */
        [[nodiscard]] iterator find(const Json & item);

        /*!
         * @brief Returns a const_iterator to the Json object related to given JsonKey.
         * @param key A const reference to JsonKey object
         * @throw exceptions::InvalidOperation Throws when the Json object type is not JsonObject.
         * @return const_iterator pointing to the object related to the given JsonKey. If the given key is not found
         * this->cend() would be returned instead.
         */
        [[nodiscard]] const_iterator find(const JsonKey & key) const;

        /*!
         * @brief Returns a const_iterator to the given Json in the container.
         * @param item A const reference to Json object
         * @throw exceptions::InvalidOperation Throws when the Json object type is not iterable(container).
         * @return const_iterator pointing to the found object inside Json container. If the Json object is not found
         * this->cend() would be returned instead.
         */
        [[nodiscard]] const_iterator find(const Json & item) const;

        /*!
         * @brief Returns an iterator to the item that passed the given test function.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not Array.
         * @param test_func A const reference to test function object
         * @return An iterator pointing to the first item that passed the test or this->end() if none of them passed it.
         */
        [[nodiscard]] iterator find_if(const std::function<bool(const Json &)> & test_func);

        /*!
         * @brief Returns a const_iterator to the item that passed the given test function.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not Array.
         * @param test_func A const reference to test function object
         * @return A const_iterator pointing to the first item that passed the test or this->cend() if none of
         * them passed it.
         */
        [[nodiscard]] const_iterator find_if(const std::function<bool(const Json &)> & test_func) const;

        /*!
         * @brief Returns an iterator to the item that passed the given test function.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not JsonObject.
         * @param test_func A const reference to test function object
         * @return An iterator pointing to the first item that passed the test or this->end() if none of them passed it.
         */
        [[nodiscard]] iterator find_if(const std::function<bool(const pair_type &)> & test_func);

        /*!
         * @brief Returns a const_iterator to the item that passed the given test function.
         * @throw exceptions::InvalidOperation Throws if the Json object type is not JsonObject.
         * @param test_func A const reference to test function object
         * @return A const_iterator pointing to the first item that passed the test or this->cend() if none of
         * them passed it.
         */
        [[nodiscard]] const_iterator find_if(const std::function<bool(const pair_type &)> & test_func) const;

        /*!
         * @brief Returns the index of given Json object inside Array.
         * @param item A const reference to the Json object that is going to be checked inside the Array.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not Array.
         * @return size_t index of given Json object inside the Array
         */
        [[nodiscard]] size_t find_index(const Json & item) const;

        /*!
         * @brief Returns the index of Json object related to the given const_iterator inside Array.
         * @param it A const reference to the const_iterator that is going to be checked inside the Array.
         * @throw exceptions::InvalidOperation Throws when the Json object type is not Array.
         * @return size_t index of Json object related to the given const_iterator inside the Array.
         */
        [[nodiscard]] size_t find_index(const const_iterator & it) const;

        /*!
         * @brief Returns the size of the container stored inside Json object.
         *
         * If the data type is not a container 1 will be returned as size.
         * If the data type is not unknown then a 0 will be returned.
         * @return size_t size of the Json object
         */
        [[nodiscard]] size_t size() const noexcept;

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
        [[nodiscard]] long & get_int();

        /*!
         * @brief double data getter
         * @return A reference to double data stored inside
         */
        [[nodiscard]] double & get_double();

        /*!
         * @brief bool data getter
         * @return A reference to bool data stored inside
         */
        [[nodiscard]] bool & get_bool();

        /*!
         * @brief std::string data getter
         * @return A reference to std::string data stored inside
         */
        [[nodiscard]] std::string & get_string();

        /*!
         * @brief Array data getter
         * @return A reference to Array data stored inside
         */
        [[nodiscard]] Array & get_array();

        /*!
         * @brief JsonObject data getter
         * @return A reference to JsonObject data stored inside
         */
        [[nodiscard]] JsonObject & get_json_object();

        /*!
         * @brief Finds the given Json object in the given range.
         * @tparam T Type of given iterators
         * @param first First iterator in the range
         * @param last Last iterator in the range
         * @param item A const reference to the target Json object
         * @throw iterators::exceptions::InvalidIteration Throws when the iterator is not an Array iterator.
         * @return The iterator with the given type pointing to the given item in the container. If the item
         * does not exist in the range iterator pointing to this->end() will be returned instead.
         */
        template<typename T>
        [[nodiscard]] T find_in_range(const T & first, const T & last, const Json & item) const {
            first.check_type(IteratorTypes::array_iterator_type);
            last.check_type(IteratorTypes::array_iterator_type);
            return T{std::find(*first.array_iterator, *last.array_iterator, item)};
        }

        /*!
         * @brief Counts the instances of the given Json object in the given range.
         * @tparam T Type of given iterators
         * @param first First iterator in the range
         * @param last Last iterator in the range
         * @param item A const reference to the target Json object
         * @throw iterators::exceptions::InvalidIteration Throws when the iterator is not an Array iterator.
         * @return size_t count of instances of the given Json object in the container.
         */
        template<typename T>
        [[nodiscard]] size_t count_in_range(const T & first, const T & last, const Json & item) const {
            first.check_type(IteratorTypes::array_iterator_type);
            last.check_type(IteratorTypes::array_iterator_type);
            return std::count(* first.array_iterator, * last.array_iterator, item);
        }

        // Destructors
        ~Json();
    };

    /*!
     * @relatedalso Json
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
