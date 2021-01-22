
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
#include <algorithm>

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
            void compare_array(const JsonPointer & path);
            void compare_json_object(const JsonPointer & path);
            void remove_item(const JsonPointer & path);
            void add_item(const JsonPointer & path, const Json & item);
            void replace_item(const JsonPointer & path, const Json & item);
            void move_item(const JsonPointer & old_path, const JsonPointer & new_path);
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
