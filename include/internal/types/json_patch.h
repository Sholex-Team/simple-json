
#ifndef SIMPLE_JSON_JSON_PATCH_H
#define SIMPLE_JSON_JSON_PATCH_H

#include <string>
#include "json_pointer.h"
#include "json_utils.h"
#include "json.h"

namespace simple_json::types {
    class Json;

    class JsonPatch {
    private:
        Json * patch_data;
    public:

        // Constructors
        JsonPatch(const Json &);
        JsonPatch(const JsonPatch &);
        JsonPatch(JsonPatch &&) noexcept;

        // Destructors
        ~JsonPatch();

        // Public Method
        void patch(Json &);
    };
}


#endif //SIMPLE_JSON_JSON_PATCH_H
