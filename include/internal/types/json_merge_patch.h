#ifndef SIMPLE_JSON_JSON_MERGE_PATCH_H
#define SIMPLE_JSON_JSON_MERGE_PATCH_H

#include "json.h"

namespace simple_json::types {
    Json apply_merge_patch(Json target_json, const Json & merge_patch);
}

#endif //SIMPLE_JSON_JSON_MERGE_PATCH_H
