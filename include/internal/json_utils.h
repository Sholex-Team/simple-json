#ifndef SIMPLE_JSON_JSON_UTILS_H
#define SIMPLE_JSON_JSON_UTILS_H

#include <vector>
#include <string>
#include "types/enum_types.h"

namespace simple_json::utils {
    /*!
     * @brief Takes a string and splits it based on a word.
     * @param base string which is going to turn into a vector using the target word.
     * @param target The word which is going to be used for splitting the base string.
     * @return std::vector containing parts of base string parted using the target word.
     */
    std::vector<std::string> split(std::string base, const std::string & target);

    /*!
     * @brief Checks if the whole std::string is created by digits.
     *
     * This function will check the string characters one by one and detects if all of them are digits.
     * @param str The base string which is going to be checked.
     * @return A boolean telling whether the string was created all by digits or not.
     */
    [[nodiscard]] bool is_digit(const std::string & str);

    /*!
     * @brief Replaces a(or more) word(s) with another(more or less) word(s) inside a std::string.
     *
     * This function can replace a value containing one or many words or characters with another value without need of
     * having the same character count as the old_value.
     * @param base [out] The base string which is going to be changed.
     * @param old_value [in] The old value which is going to be replaced with new_value.
     * @param new_value [in] The new value which is going to replace the old_value.
     */
    void replace_str(std::string & base, const std::string & old_value, const std::string & new_value);

    /*!
     * @brief Serializes a JSON Pointer string.
     * @param base [out] The JSON Pointer string which is going to get serialized.
     */
    void serialize_json_pointer(std::string & base);

    /*!
     * @brief Deserializes a JSON Pointer string.
     * @param base [out] The JSON Pointer string which is going to get deserialized.
     */
    void deserialize_json_pointer(std::string & base);

    /*!
     * @brief Returns the string representation of a DataType value.
     * @param type DataType value
     * @return const char * of the c-string representation
     */
    [[nodiscard]] const char * json_type_to_string(const simple_json::types::DataType & type);
}

/*! @namespace simple_json::utils
 * @brief JSON related utilities
 *
 * This namespace contains functions which are used in different parts of simple_json for simple tasks such as splitting
 * texts or replacing words in a std::string.
 */

#endif //SIMPLE_JSON_JSON_UTILS_H
