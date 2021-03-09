#ifndef SIMPLE_JSON_INVALID_OPERATION_H
#define SIMPLE_JSON_INVALID_OPERATION_H

#include "base_exception.h"
#include "../enum_types.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Invalid Operation exception.
     *
     * This exception throws when there is an invalid operation happening on a Json object.
     */
    class InvalidOperation : public base_exceptions::JsonException {
    private:
        DataType used_type;
    public:
        // Constructors
        /*!
         * @brief InvalidOperation constructor.
         *
         * This constructor takes an optional argument which represents Json object data type being used in an
         * operation.
         * @param used_type The type of Json object which is being used in the operation.
         */
        explicit InvalidOperation(DataType used_type = DataType::unknown);

        // Public Methods
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_INVALID_OPERATION_H
