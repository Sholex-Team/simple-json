#ifndef SIMPLE_JSON_STREAM_EXCEPTIONS_H
#define SIMPLE_JSON_STREAM_EXCEPTIONS_H

#include "base_exception.h"

class StreamInsertionException : public JsonException {
public:
    const char * what() const noexcept override;
};

#endif //SIMPLE_JSON_STREAM_EXCEPTIONS_H
