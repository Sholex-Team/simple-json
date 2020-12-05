#ifndef SIMPLE_JSON_STREAM_EXCEPTIONS_H
#define SIMPLE_JSON_STREAM_EXCEPTIONS_H

#include "base_exception.h"

namespace simple_json::types::exceptions {
    class StreamInsertionException : public JsonException {
    public:
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_STREAM_EXCEPTIONS_H
