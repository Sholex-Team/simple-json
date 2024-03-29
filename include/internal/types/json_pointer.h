#ifndef SIMPLE_JSON_JSON_POINTER_H
#define SIMPLE_JSON_JSON_POINTER_H

#include <string>
#include <vector>
#include "../json_utils.h"
#include "json_key.h"
#include "exceptions/invalid_pointer.h"
#include "enum_types.h"
#include <cstdlib>

namespace simple_json::types {
    class Json;
    class JsonPatch;

    /*!
     * @brief Json Pointer class.
     *
     * This class is used to create objects storing JSON Pointers.
     */
    class JsonPointer {
    private:
        // Properties
        std::string * pointer_text;
        std::vector<std::string> * pointer_list;

        // Private Methods
        void check_pointer(DataType used_type) const;
    public:
        // Constructors
        /*!
         * @brief JsonPointer string constructor
         *
         * This constructor copies a std::string into a new JsonPointer as JSON Pointer string.
         * @throw exceptions::InvalidPointer Throws if pointer_text is invalid.
         * @param pointer_text A L-Value reference to a std::string which is about to get copied as JSON Pointer string.
         */
        [[nodiscard]] explicit JsonPointer(std::string & pointer_text);

        /*!
         * @throw exceptions::InvalidPointer Throws if pointer_text is invalid.
         * @brief JsonPointer string constructor.
         *
         * This constructor moves a std::string into a new JsonPointer as JSON Pointer string.
         * @param pointer_text A R-Value reference to a std::string which is about to get moved as JSON pointer string.
         */
        [[nodiscard]] explicit JsonPointer(std::string && pointer_text);

        /*!
         * @brief JsonPointer copy constructor
         * @param json_pointer Const reference to a JsonPointer object which is about to get copied.
         */
        [[nodiscard]] JsonPointer(const JsonPointer & json_pointer);

        /*!
         * @brief JsonPointer move constructor
         * @param json_pointer A r-value reference to a JsonPointer object which is about to get moved.
         */
        [[nodiscard]] JsonPointer(JsonPointer && json_pointer) noexcept;

        // Destructors
        ~JsonPointer();

        // Public Methods
        /*!
         * @brief Adds a string index to pointer
         *
         * This public method adds a new key index to JsonPointer.
         * @param path String key which is going to get added
         */
        void add_to_path(std::string path);

        /*!
         * @brief Adds a index to pointer
         *
         * This public method adds a new index to JsonPointer.
         * @param index Index which is going to get added
         */
        void add_to_path(size_t index);

        /*!
         * @brief Returns last index in pointer
         * @throw exceptions::InvalidPointer Throws if last index is not a size_t value.
         * @return size_t which is the last index inside the JsonPointer
         */
        [[nodiscard]] size_t get_index() const;

        /*!
         * @brief Returns last key in pointer
         * @return JsonKey which is the last string index in the JsonPointer
         * @throw exceptions::InvalidPointer Throws if last index is not a JsonKey object.
         */
        [[nodiscard]] JsonKey get_key() const;

        /*!
         * @brief Returns last index parent
         *
         * This public method removes last index inside the JsonPointer and returns the remains of pointer as a new
         * JsonPointer object.
         * @throw exceptions::InvalidPointer Throws if pointer does not have a parent.
         * @return New JsonPointer object created from current JsonPointer object's parent.
         */
        [[nodiscard]] JsonPointer get_parent() const;

        /*!
         * @brief Checks if pointer ends with "-" character.
         * @return A boolean specifying if pointer ended with "-" character.
         */
        [[nodiscard]] bool check_ended() const;

        // Operator Overloading

        /*!
         * @brief Checks if two JsonPointer objects are equal.
         * @param json_pointer JsonPointer which is going to get compared.
         * @return A boolean representing the checking result.
         */
        [[nodiscard]] bool operator==(const JsonPointer & json_pointer) const;

        /*!
         * @brief Addition operator overload
         *
         * This operator overload adds a string key to a copy of current JsonPointer object and returns the copy.
         * @param r_path std::string which is going to get added to the pointer
         * @return Created JsonPointer object
         */
        [[nodiscard]] JsonPointer operator+(const std::string & r_path) const;

        /*!
         * @brief Addition operator overload
         *
         * This operator overload adds a JsonKey object to a copy of current JsonPointer object and returns the copy.
         * @param r_path JsonKey object which is going to be added to current pointer.
         * @return New JsonPointer object created from adding r_path to current JsonPointer object.
         */
        [[nodiscard]] JsonPointer operator+(const JsonKey & r_path) const;

        /*!
         * @brief Addition operator overload
         *
         * This operator overload adds a size_t index to a copy of current JsonPointer object and returns the copy.
         * @param r_index size_t index which is going to get added to the current pointer.
         * @return New JsonPointer object created from adding r_path to current JsonPointer object.
         */
        [[nodiscard]] JsonPointer operator+(size_t r_index) const;

        /*!
         * @brief std::string explicit conversion operator
         *
         * This operator overload returns a copy of JsonPointer inner pointer_text which is a std::string object.
         * @return A copy of pointer_text inside the current JsonPointer object.
         */
        [[nodiscard]] explicit operator std::string() const;

        // Friends
        friend std::ostream & operator<<(std::ostream &, const JsonPointer &);
        friend class Json;
        friend class JsonKey;
    };

    // Operator Overloading

    /*!
     * @brief User-Defined literal operator overload
     *
     * This overload provides ability to create a JsonPointer from a string literal using ""_ syntax.
     * @param pointer_ptr Pointer pointing to first character of c-string that operator is being used on.
     * @return A new JsonPointer object created from a c-string.
     */
    [[nodiscard]] JsonPointer operator""_json_ptr(const char * pointer_ptr, size_t);

    /*!
     * @relatedalso JsonPointer
     * @brief Overloaded stream insertion operator
     *
     * This overloaded operator is used during serialization of JsonPointer object.
     * @param os Output Stream
     * @param json_pointer JsonPointer which is about to get serialized.
     * @return A reference to the std::ostream object passed into the function.
     */
    std::ostream & operator<<(std::ostream & os, const JsonPointer & json_pointer);
}

#endif //SIMPLE_JSON_JSON_POINTER_H
