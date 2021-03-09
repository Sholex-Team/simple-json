#ifndef SIMPLE_JSON_INVALID_PATCH_OPERATION_H
#define SIMPLE_JSON_INVALID_PATCH_OPERATION_H

#include <string>
#include "base_exception.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Invalid Patch Operation exception.
     *
     * This exception throws when there is an invalid operation in a JsonPatch object.
     */
    class InvalidPatchOperation : public base_exceptions::JsonException {
    public:
        // Public Methods
        const char * what() const noexcept override;
    };
}

#endif
