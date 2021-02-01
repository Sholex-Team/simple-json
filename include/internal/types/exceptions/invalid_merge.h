#ifndef SIMPLE_JSON_INVALID_MERGE_H
#define SIMPLE_JSON_INVALID_MERGE_H

#include "base_exception.h"
#include "types/enum_types.h"

namespace simple_json::types::exceptions {
    class InvalidMerge : public base_exceptions::JsonException {
    private:
        DataType target_type;
    public:
        InvalidMerge(DataType target_type = DataType::unknown);
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_INVALID_MERGE_H
