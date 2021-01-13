#ifndef SIMPLE_JSON_INVALID_INDEX_H
#define SIMPLE_JSON_INVALID_INDEX_H

#include "base_exception.h"
#include "types/enum_types.h"

namespace simple_json::types::exceptions {
        class InvalidIndexException : public base_exceptions::JsonException {
        private:
            DataType used_type;
        public:
            const char * what() const noexcept override;
            explicit InvalidIndexException(DataType used_type = DataType::unknown);
        };
    }

#endif //SIMPLE_JSON_INVALID_INDEX_H
