#ifndef SIMPLE_JSON_FAILED_TEST_H
#define SIMPLE_JSON_FAILED_TEST_H

#include "base_exceptions.h"
#include <string>
#include <cinttypes>
#include "../json_pointer.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief JsonPointer failed test exception.
     *
     * This exceptions is thrown when a JsonPointer test fails.
     */
    class FailedTest : public base_exceptions::JsonException {
    private:
        std::string error_text;
    public:
        // Error Types
        /*! @enum
         * @brief Different types of test failure errors.
         */
        enum class Error : std::uint8_t {
            INVALID_VALUE, /*!< Used when test fails because of invalid value of given path. */
            INVALID_PATH /*!< Used when the given path does not exist. */
        };

        // Constructors
        /*!
         * @brief Failed Test exception constructor.
         * @param json_pointer A const reference to the JsonPointer which exception occurred at.
         * @param error Type of the exception.
         */
        explicit FailedTest(const JsonPointer & json_pointer, Error error = Error::INVALID_VALUE);

        // Public Methods
        [[nodiscard]] const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_FAILED_TEST_H
