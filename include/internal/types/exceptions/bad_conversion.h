#ifndef SIMPLE_JSON_BAD_CONVERSION_H
#define SIMPLE_JSON_BAD_CONVERSION_H

#include "base_exception.h"
#include "../enum_types.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Conversion exceptions.
     *
     * This exception happens when is thrown when an invalid conversion is happening from a Json object to an unrelated
     * type.
     * e.g : Json(used_type = DataType::integer_type) -> std::string.
     */
    class BadConversion : public base_exceptions::JsonException {
    private:
        DataType to;
    public:
        const char * what() const noexcept override;

        /*!
         * BadConversion constructor.
         *
         * This constructor takes an optional parameter which is the invalid destination type of conversion.
         * @param to Invalid destination type.
         */
        explicit BadConversion(DataType to = DataType::unknown) noexcept;
    };
}

/*! @namespace simple_json::types::exceptions
 * @brief Namespace dedicated to typography related exceptions.
 *
 * This namespace contains exceptions related to special types of the project.
 */

#endif
