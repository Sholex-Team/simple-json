#ifndef SIMPLE_JSON_INVALID_OPERATOR_H
#define SIMPLE_JSON_INVALID_OPERATOR_H

#include "base_exception.h"
#include "types/enum_types.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Invalid Operator exception.
     *
     * This exception is thrown when an operator is used on an invalid type.
     */
    class InvalidOperator : public base_exceptions::JsonException {
    private:
        DataType used_type{};
    public:
        // Constructors
        explicit InvalidOperator(DataType target_type = DataType::unknown);

        // Public Methods
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_INVALID_OPERATOR_H
