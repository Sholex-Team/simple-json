#ifndef SIMPLE_JSON_FAILED_TEST_H
#define SIMPLE_JSON_FAILED_TEST_H

#include "base_exception.h"

namespace simple_json::types::exceptions {
    class FailedTest : public base_exceptions::JsonException {
    public:
        // Public Methods
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_FAILED_TEST_H
