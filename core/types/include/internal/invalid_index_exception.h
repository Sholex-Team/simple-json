
#ifndef SIMPLE_JSON_INVALID_INDEX_EXCEPTION_H
#define SIMPLE_JSON_INVALID_INDEX_EXCEPTION_H

#include "base_exception.h"
#include "enum_types.h"

class InvalidIndexException : public JsonException {
private:
    DataType to;
public:
    const char * what() const noexcept override;
    InvalidIndexException(DataType) noexcept;
    InvalidIndexException() noexcept : JsonException(), to {DataType::unknown} {}
};

#endif //SIMPLE_JSON_INVALID_INDEX_EXCEPTION_H
