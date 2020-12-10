#ifndef SIMPLE_JSON_STREAM_EXCEPTIONS_H
#define SIMPLE_JSON_STREAM_EXCEPTIONS_H

#include "base_exception.h"
#include "array_type.h"

namespace simple_json::serializer::exceptions {

class StreamInsertionException : public simple_json::base_exceptions::JsonException {
    public:
        const char * what() const noexcept override;
    };

    class WritingToFileException : public simple_json::base_exceptions::JsonException {
    public:
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_STREAM_EXCEPTIONS_H
