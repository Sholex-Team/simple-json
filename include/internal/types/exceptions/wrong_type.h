#ifndef SIMPLE_JSON_WRONG_TYPE_H
#define SIMPLE_JSON_WRONG_TYPE_H

#include "base_exception.h"
#include "../enum_types.h"

namespace simple_json::types::exceptions {
    class WrongType : public base_exceptions::JsonException {
    private:
        DataType used_type;
    public:
        // Constructors
        WrongType(DataType used_type = DataType::unknown);

        // Public Methods
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_WRONG_TYPE_H
