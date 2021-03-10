#ifndef SIMPLE_JSON_DESERIALIZER_EXCEPTIONS_H
#define SIMPLE_JSON_DESERIALIZER_EXCEPTIONS_H

#include "base_exception.h"
#include <cinttypes>

namespace simple_json::deserializer::exceptions {
    /*!
     * @brief Parsing Exception thrown when serialized JSON is invalid.
     *
     * This exceptions will be thrown during deserialization if the serialized string/ifstream data is invalid.
     */
    class ParsingException : public base_exceptions::JsonException {
    public:
        enum class Errors : std::uint8_t {
            illegal_array_split, /*!< Used when there is an illegal "," inside the serialized JSON. */
            illegal_key_split, /*!< Used when there is an illegal ":" inside the serialized JSON. */
            illegal_escape, /*!< Used when there is an illegal "\" inside the serialized JSON. */
            empty_key, /*!< Used when there is a empty key ("": ) inside the serialized JSON. */
            invalid_key, /*!< Used when JSON Object key is invalid. */
            invalid_array, /*!< Used when there is an illegal "[" inside the serialized JSON. */
            invalid_string, /*!< Used when there is an illegal '"' inside the serialized JSON. */
            illegal_space, /*!< Used when there is an illegal " " inside the serialized JSON. */
            invalid_character, /*!< Used then there is a random invalid character inside the serialized JSON. */
            extra_character, /*!< Used when there is an character after closing all arrays and JSON Objects. */

            /*!
             * Used when an escape sequence is used in an invalid place such as JSON Object keys.
             */
            illegal_escape_sequences,
            unfinished_json, /*!< Used when arrays or JSON Objects remain open. */

            /*!
             * Used when cause of error is not identified or there is no specific type passed to exceptions constructor.
             */
            unknown
        };

        /*! @enum Errors
         * @brief Different types of parsing errors.
         *
         * These types are used when an ParsingException is being thrown.
         */

        // Constructors
        /*!
         * @brief Parsing Exception constructor.
         *
         * This constructor takes an optional error type parameter which is simply the cause of deserialization error.
         * @param error
         */
        explicit ParsingException(Errors error = Errors::unknown);

        // Public Methods
        const char * what() const noexcept override;
    private:
        Errors error;
    };
}

/*! @namespace simple_json::deserializer::exceptions
 * @brief Namespace dedicated to deserializer related exceptions.
 *
 * Every single exceptions thrown from deserializers are located here.
 */

#endif //SIMPLE_JSON_DESERIALIZER_EXCEPTIONS_H
