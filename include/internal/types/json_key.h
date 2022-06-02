#ifndef SIMPLE_JSON_JSON_KEY_H
#define SIMPLE_JSON_JSON_KEY_H

#include <string>
#include <iostream>

namespace simple_json::types {
    class JsonObject;

    /*!
     * @brief Json Key class
     *
     * Objects created from this class are used as the keys in JsonObject objects which is derived from std::map<Json>.
     */
    class JsonKey {
    private:
        std::string * key;
    public:
        // Constructors
        /*!
         * @brief JsonKey constructor
         *
         * This constructor accepts an argument as key string which is then used as key underneath the JsonKey object.
         * @param key std::string which the JsonKey is going to be created from
         */
        [[nodiscard]] explicit JsonKey(const std::string & key);

        /*!
         * @brief JsonKey copy constructor
         * @param json_key JsonKey object which is about to get copied
         */
        [[nodiscard]] JsonKey(const JsonKey & json_key);

        /*!
         * @brief JsonKey move constructor
         * @param json_key JsonKey which is about to get moved
         */
        [[nodiscard]] JsonKey(JsonKey && json_key) noexcept;

        // Destructors
        ~JsonKey();

        // Operators
        /*!
         * @brief Less than operator overload
         * @param r_json_key JsonKey object on RHS
         * @return A boolean specifying if the JsonKey was less than RHS one.
         */
        [[nodiscard]] bool operator<(const JsonKey & r_json_key) const;

        /*!
         * @brief Greater than operator overload.
         * @param r_json_key JsonKey object on RHS
         * @return A boolean specifying if the JsonKey was greater than RHS one.
         */
        [[nodiscard]] bool operator>(const JsonKey & r_json_key) const;

        /*!
         * @brief Equal operator overload
         * @param r_json_key JsonKey object on RHS
         * @return A boolean specifying if the JsonKey was equal with RHS one.
         */
        [[nodiscard]] bool operator==(const JsonKey & r_json_key) const;

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const JsonKey & json_key);
        friend class JsonObject;

        // Public Methods
        /*!
         * @brief Returns the key string.
         *
         * This public method returns inner std::string stored as key inside JsonKey object.
         * @return std::string stored inside JsonKey.
         */
        [[nodiscard]] inline const std::string & get_key() const {return * key;};
    };

    // Operator Overloading
    /*!
     * @brief User-Defined literal operator overload.
     *
     * This overload provides ability to create a JsonKey from a string literal using ""_ syntax.
     * @param key_ptr Pointer pointing to first character of c-string that operator is being used on.
     * @return A new JsonKey object created from a c-string
     */
    [[nodiscard]] JsonKey operator""_json_key(const char * key_ptr, size_t);

    /*!
     * @brief Overloaded stream insertion operator.
     *
     * This overloaded operator is used during serialization of JsonKey object.
     * @param os Output Stream
     * @param json_key JsonKey which is about to get serialized
     * @return A reference to Output Stream object passed into the function.
     */
    std::ostream & operator<<(std::ostream & os, const JsonKey & json_key);
}

#endif //SIMPLE_JSON_JSON_KEY_H
