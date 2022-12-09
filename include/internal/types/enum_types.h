#ifndef SIMPLE_JSON_ENUM_TYPES_H
#define SIMPLE_JSON_ENUM_TYPES_H

#include <cinttypes>
#include <string>

namespace simple_json::types {
    enum DataType : std::size_t {
        /*!
         * This type is used when an empty Json object is created without any type or data. Usually there is no
         * use case for it outside of deserializer and PatchBuilder.
         */
        unknown,
        null_type, /*!< This type represents null values in JSON. */
        integer_type, /*!< This type represents a signed long int which is biggest integer data type in CPP .*/
        double_type, /*!< This type represents a double which is the fractional data type. */
        boolean_type, /*!< This type represents booleans used in JSON */
        string_type, /*!< This type represents a std::string type which is used instead of c-string. */

        /*!
         * This type represents arrays in JSON that are stored in a Json object using Array type.
         */
        array_type,

        /*!
         * This type represents JSON Objects in JSON that are stored in a Json object using JsonObject type.
         */
        json_object_type,
        string_key_type, /*!< This type represents JsonKey which is used inside a JsonObject as key of the map. */

        /*!
         * This type represents special types such as null, false, and true. it's only used inside the deserializer
         * and there is no use case for it outside.
         */
        special_type,
    };

    /*! @enum DataType
     * @brief JSON data types.
     *
     * These types will be used for specifying Json object inner type.
     */

    enum IteratorType : std::size_t  {
        unknown_iterator, /*!< This type will be used when the iterator type is not defined yet. */
        array_iterator_type, /*!< This type will be used if iterator is Array based. */
        json_object_iterator_type /*!< This type will be used if iterator is JsonObject based. */
    };

    /*! @enum IteratorType
     * @brief Json Iterator types.
     *
     * This types will be used inside a JsonIterator based iterator to specify it's inner type.
     */
}

#endif //SIMPLE_JSON_ENUM_TYPES_H
