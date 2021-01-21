
#ifndef SIMPLE_JSON_JSON_PATCH_H
#define SIMPLE_JSON_JSON_PATCH_H

#include <string>
#include "json_pointer.h"
#include "json_utils.h"
#include "json.h"
#include "exceptions/invalid_index.h"
#include "exceptions/invalid_operation.h"
#include "exceptions/failed_test.h"
#include "json_key.h"

namespace simple_json::types {
    class Json;

    class JsonPatch {
    private:
        Json * patch_data;
    public:
        // Constructors
        JsonPatch();
        JsonPatch(const Json &);
        JsonPatch(const JsonPatch &);
        JsonPatch(JsonPatch &&) noexcept;

        // Destructors
        ~JsonPatch();

        // Public Method
        void patch(Json &);

        // Builders
        class PatchBuilder {
        private:
            // Properties
            JsonPatch * new_patch {};
            Json * src;
            Json * dst;
            Json * current_src;
            Json * current_dst;

            // Private Methods
            void compare_array();
            void compare_json_object();
        public:
            // Constructor
            PatchBuilder(const Json & src, const Json & dst);

            // Destructor
            ~PatchBuilder();

            // Public Methods
            JsonPatch create_patch();
        };

        // Friends
        friend PatchBuilder;
    };
}


#endif //SIMPLE_JSON_JSON_PATCH_H
