#ifndef SIMPLE_JSON_INVALID_POINTER_H
#define SIMPLE_JSON_INVALID_POINTER_H

#include "base_exception.h"

namespace simple_json::types::exceptions {
    class InvalidPointer : public base_exceptions::JsonException {
    public:
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_INVALID_POINTER_H
