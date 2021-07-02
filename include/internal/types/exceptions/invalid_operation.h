#ifndef SIMPLE_JSON_INVALID_OPERATION_H
#define SIMPLE_JSON_INVALID_OPERATION_H

#include "base_exceptions.h"
#include "../enum_types.h"
#include "../../json_utils.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Invalid Operation exception.
     *
     * This exception throws when there is an invalid operation happening on a Json object.
     */
    class InvalidOperation : public base_exceptions::JsonErrorTextException {
    public:
        // Constructors
        /*!
         * @brief InvalidOperation constructor.
         *
         * This constructor takes an optional argument which represents Json object data type being used in an
         * operation.
         * @param used_type The type of Json object which is being used in the operation.
         */
        explicit InvalidOperation(DataType used_type = DataType::unknown, DataType operation_type = DataType::unknown);
    };
}

#endif //SIMPLE_JSON_INVALID_OPERATION_H
