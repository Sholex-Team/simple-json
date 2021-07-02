#ifndef SIMPLE_JSON_INVALID_POINTER_H
#define SIMPLE_JSON_INVALID_POINTER_H

#include "base_exceptions.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Invalid Pointer exception.
     *
     * This exception throws when used Json Pointer string is invalid.
     */
    class InvalidPointer : public base_exceptions::JsonException {
    public:
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_INVALID_POINTER_H
