
#ifndef SIMPLE_JSON_INVALID_OPERATOR_H
#define SIMPLE_JSON_INVALID_OPERATOR_H

#include "base_exception.h"

namespace simple_json::types::exceptions {
    class InvalidOperator : public base_exceptions::JsonException {};
}

#endif //SIMPLE_JSON_INVALID_OPERATOR_H
