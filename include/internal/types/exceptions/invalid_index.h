#ifndef SIMPLE_JSON_INVALID_INDEX_H
#define SIMPLE_JSON_INVALID_INDEX_H

#include "base_exception.h"
#include "types/enum_types.h"

namespace simple_json::types::exceptions {
        class InvalidIndexException : public base_exceptions::JsonException {
        private:
            DataType to;
        public:
            const char * what() const noexcept override;
            explicit InvalidIndexException(DataType) noexcept;
            InvalidIndexException() noexcept : JsonException(), to {DataType::unknown} {}
        };
    }

#endif //SIMPLE_JSON_INVALID_INDEX_H
