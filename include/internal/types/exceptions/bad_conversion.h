#ifndef SIMPLE_JSON_BAD_CONVERSION_H
#define SIMPLE_JSON_BAD_CONVERSION_H

#include "base_exceptions.h"
#include "../enum_types.h"
#include <string>
#include "../../json_utils.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief BadConversion exception.
     *
     * This exception is thrown when an invalid conversion is tried from a Json object to an unrelated
     * type.
     */
    class BadConversion : public base_exceptions::JsonErrorTextException {
    public:
        // Constructors
        /*!
         * BadConversion exception constructor.
         * @param src Source Type
         * @param dst Invalid Destination Type
         */
        explicit BadConversion(DataType src = DataType::unknown, DataType dst = DataType::unknown) noexcept;
    };
}

/*! @namespace simple_json::types::exceptions
 * @brief Namespace dedicated to typography related exceptions.
 *
 * This namespace contains exceptions related to special types of the project.
 */

#endif
