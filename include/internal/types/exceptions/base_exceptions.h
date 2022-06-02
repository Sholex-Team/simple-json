#ifndef SIMPLE_JSON_BASE_EXCEPTIONS_H
#define SIMPLE_JSON_BASE_EXCEPTIONS_H

#include <exception>
#include <string>

namespace simple_json::base_exceptions {
    /*!
     * @brief Base exception.
     *
     * All other exceptions of this project are derived from this exception type.
     */
    class JsonException : public std::exception {};

    /*!
     * @brief Base exception with dynamic error text(based on types and other arguments).
     */
    class JsonErrorTextException : public JsonException {
    protected:
        // Protected Members
        std::string * error_text {new std::string {}};
    public:
        // Public Methods
        /*!
         * @brief Returns dynamically created error text.
         * @return const char * of error text
         */
        [[nodiscard]] const char * what() const noexcept override;

        // Destructor
        ~JsonErrorTextException() override;
    };
}

/*! @namespace simple_json::base_exceptions
 * @brief Namespace dedicated to base exceptions.
 *
 * This namespace contains the Base type of exceptions used in this project.
 */

#endif //SIMPLE_JSON_BASE_EXCEPTIONS_H
