#ifndef SIMPLE_JSON_INVALID_INDEX_H
#define SIMPLE_JSON_INVALID_INDEX_H

#include "base_exceptions.h"
#include "../enum_types.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Invalid Index exception.
     *
     * This exception is thrown when an invalid index is used on a Json object.
     * e.g: Using int as an index when Json object type is JsonObject.
     */
    class InvalidIndex : public base_exceptions::JsonException {
    private:
        DataType used_type;
    public:
        // Public Methods
        [[nodiscard]] const char * what() const noexcept override;

        // Constructors
        /*!
         * @brief InvalidIndex constructor.
         *
         * This constructor accepts an optional argument representing the object type which the index is being used on.
         * @param used_type Object Type.
         */
        explicit InvalidIndex(DataType used_type = DataType::UNKNOWN);
    };
}

#endif //SIMPLE_JSON_INVALID_INDEX_H
