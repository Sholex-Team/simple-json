#ifndef SIMPLE_JSON_JSON_OBJECT_H
#define SIMPLE_JSON_JSON_OBJECT_H

#include <map>
#include <string>
#include <initializer_list>
#include <utility>
#include "json_key.h"
#include "iostream"
#include <utility>
#include <iomanip>

namespace simple_json::types {
    class Json;
    class Array;
    using map_type = std::map<const JsonKey, Json>;
    using pair_type = std::pair<const JsonKey, Json>;
    using json_list_type = std::initializer_list<pair_type>;

    /*!
     * @brief Json Object class.
     *
     * This object type is derived from std::map<const JsonKey, Json> and it represents a JSON Object. Objects created
     * by this class are stored inside a Json object as key-value map.
     */
    class JsonObject : public map_type {
        private:
            std::ostream & stream_without_indent(std::ostream & os) const;
            std::ostream & stream_with_indent(std::ostream & os, size_t local_indent) const;
        public:
            // Constructors
            /*!
             * @brief JsonObject initializer list constructor.
             *
             * This constructor accept an initializer list as an argument containing pairs which are going to initialize
             * the inner map and create a new JsonObject.
             * @param initializer_list An initializer list containing std::pair<const JsonKey, Json> that are going to
             * initialize the object.
             */
            JsonObject(const json_list_type & initializer_list);

            // Friends
            friend std::ostream & operator<<(std::ostream & os, const JsonObject & json_object);
            friend Array;

            // Public Methods
            /*!
             * @brief Get a value with a key or return specified value.
             *
             * This public method tries to return a value related to given key and in case of the key not existing
             * it will return a copy of Json object given to the method.
             * @param key JsonKey key which the method is going to look it up inside the std::map.
             * @param default_return Default value which is going to get returned in case of the key not existing inside
             * the map.
             * @return A Json object whether it's the value related to the key or the default value.
             */
            Json get(const JsonKey & key, const Json & default_return) const;

            /*!
             * @brief Get a value with a key or return specified value.
             *
             * This public method tries to return a value related to given key and in case of the key not existing
             * it will return a moved object of Json object given to the method.
             * @param key JsonKey key which the method is going to look it up inside the std::map.
             * @param default_return Default value which is going to be moved into a new Json object and returned
             * in case of the key not existing inside the std::map.
             * @return A Json object whether it's the value related to the key or the moved default value.
             */
            Json get(const JsonKey & key, Json && default_return) const;

           /*!
            * @brief Get a value with a key or return specified value.
            *
            * This public method tries to return a value related to given key and in case of the key not existing
            * it will return a copy of Json object given to the method.
            * @param key std::string key which the method is going to look it up inside the std::map.
            * @param default_return Default value which is going to get returned in case of the key not existing inside
            * the map.
            * @return A Json object whether it's the value related to the key or the default value.
            */
            Json get(const std::string & key, const Json & default_return) const;

            /*!
             * @brief Get a value with a key or return specified value.
             *
             * This public method tries to return a value related to given key and in case of the key not existing
             * it will return a moved object of Json object given to the method.
             * @param key std::string key which the method is going to look it up inside the std::map.
             * @param default_return Default value which is going to be moved into a new Json object and returned
             * in case of the key not existing inside the std::map.
             * @return A Json object whether it's the value related to the key or the moved default value.
             */
            Json get(const std::string & key, Json && default_return) const;
        };

    /*!
     * @relatedalso JsonObject
     * @brief JsonObject stream insertion operator overload.
     *
     * This overloaded stream insertion operator can be used to serialize a JsonObject object or a Json object
     * containing a JsonObject object inside.
     * @param os [out] Output Stream
     * @param json_object [in] JsonObject that is going to get serialized.
     * @return A reference to the Output Stream passed into the function
     */
    std::ostream & operator<<(std::ostream & os, const JsonObject & json_object);
}

#endif //SIMPLE_JSON_JSON_OBJECT_H
