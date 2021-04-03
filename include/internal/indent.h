
#ifndef SIMPLE_JSON_INDENT_H
#define SIMPLE_JSON_INDENT_H

#include <ostream>

namespace simple_json::indent {
    struct SetIndent {};
    /*! @struct SetIndent
     * @brief Indent dummy struct.
     *
     * This struct is used as a return type for set_indent to make it work with ostream.
     */

    extern size_t indent_length;
    /*! @var indent_length
     * @brief Global indentation length.
     *
     * This length will be used as a global indent length in serialization.
     */

    /*!
     * @param length New indent size.
     * @brief Changes indent length.
     *
     * This function can be used inside a stream in order to change indentation length.
     * Checkout the example for more info.
     * @returns SetIndent
     */
    inline SetIndent set_indent(size_t length = 2)  {
        indent_length = length;
        return {};
    }

    /*!
     * @brief Sets the indentation global length to 0.
     *
     * Using this function you will be able to turn of the indentation.
     * @return SetIndent
     */
    inline SetIndent unset_indent() {
        indent_length = 0;
        return {};
    }

    /*!
     * @brief Switches the indent.
     *
     * This function will set the indent_length to new_indent and return the old value.
     * @param new_indent New indentation length.
     * @return Indentation old value.
     */
    size_t switch_indent(size_t new_indent);

    /*!
     * @relatedalso SetIndent
     * @brief << operator overload.
     *
     * This overload will provide the ability to use set_indent and unset_indent
     * inside streams.
     * @param[out] os Output stream.
     * @param[in] dummy_struct  Dummy SetIndent struct.
     * @return Output stream.
     */
    inline std::ostream & operator<<(std::ostream & os, const SetIndent & dummy_struct) {
        return os;
    }
}

/*! @namespace simple_json::indent
 * @brief This namespace is dedicated to indentation.
 *
 * Using the functions and variables provided by this namespace, your will be able to control indentation applied on
 * ostream during serialization process.
 */

/*! @example indent.cpp
 * @brief Indentation Usage example.
*/

#endif //SIMPLE_JSON_INDENT_H
