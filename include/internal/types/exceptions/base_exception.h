#ifndef SIMPLE_JSON_BASE_EXCEPTION_H
#define SIMPLE_JSON_BASE_EXCEPTION_H

#include <exception>

namespace simple_json::base_exceptions {
    /*!
     * @brief Base exception.
     *
     * All other exceptions of this project are derived from this exception type.
     */
    class JsonException : public std::exception {};
}

/*! @namespace simple_json::base_exceptions
 * @brief Namespace dedicated to base exceptions.
 *
 * This namespace contains the Base type of exceptions used in this project.
 */

#endif //SIMPLE_JSON_BASE_EXCEPTION_H
