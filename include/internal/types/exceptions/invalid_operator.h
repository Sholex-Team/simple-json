
#ifndef SIMPLE_JSON_INVALID_OPERATOR_H
#define SIMPLE_JSON_INVALID_OPERATOR_H

#include "base_exception.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Invalid Operator exception.
     *
     * This exception is thrown when an operator is used on an invalid type.
     */
    class InvalidOperator : public base_exceptions::JsonException {};
}

#endif //SIMPLE_JSON_INVALID_OPERATOR_H
