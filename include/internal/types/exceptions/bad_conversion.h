#ifndef SIMPLE_JSON_BAD_CONVERSION_H
#define SIMPLE_JSON_BAD_CONVERSION_H

#include "base_exception.h"
#include "../enum_types.h"
#include <string>
#include "json_utils.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Conversion exceptions.
     *
     * This exception happens when is thrown when an invalid conversion is tried from a Json object to an unrelated
     * type.
     */
    class BadConversion : public base_exceptions::JsonException {
    private:
        std::string error_text;
    public:
        const char * what() const noexcept override;

        /*!
         * BadConversion exception constructor.
         * @param src Source Type
         * @param dst Invalid Destination Type
         */
        explicit BadConversion(const DataType src = DataType::unknown, const DataType dst = DataType::unknown) noexcept;
    };
}

/*! @namespace simple_json::types::exceptions
 * @brief Namespace dedicated to typography related exceptions.
 *
 * This namespace contains exceptions related to special types of the project.
 */

#endif
