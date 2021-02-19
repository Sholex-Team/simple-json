#ifndef SIMPLE_JSON_BAD_CONVERSION_H
#define SIMPLE_JSON_BAD_CONVERSION_H

#include "base_exception.h"
#include "../enum_types.h"

namespace simple_json::types::exceptions {
        class BadConversion : public base_exceptions::JsonException {
        private:
            DataType to;
        public:
            const char * what() const noexcept override;
            explicit BadConversion(DataType to) noexcept;
            BadConversion() noexcept : JsonException(), to {DataType::unknown} {}
        };
    }

#endif
