#ifndef SIMPLE_JSON_INVALID_MERGE_H
#define SIMPLE_JSON_INVALID_MERGE_H

#include "base_exceptions.h"
#include "../enum_types.h"

namespace simple_json::types::exceptions {
    /*!
     * @brief Invalid Merge exception.
     *
     * This exception is thrown when an invalid merge operation is happening.
     */
    class InvalidMerge : public base_exceptions::JsonException {
    private:
        // Private Properties
        DataType target_type;
    public:
        // Constructors
        /*!
         * @brief Invalid Merge exception constructor.
         *
         * This constructor takes an optional argument which is the merge target type and generates the proper error for
         * it. If there isn't any type provided a simple error with no typing details will be thrown.
         * @param target_type Merge target type.
         */
        explicit InvalidMerge(DataType target_type = DataType::unknown);
        
        // Public Methods
        [[nodiscard]] const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_INVALID_MERGE_H
