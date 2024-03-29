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
         * @param used_type The type of Json object which is being used in the operation
         * @param operation_type DataType which the operation can be performed on
         */
        explicit InvalidOperation(DataType used_type = DataType::UNKNOWN, DataType operation_type = DataType::UNKNOWN);
    };
}

#endif //SIMPLE_JSON_INVALID_OPERATION_H
