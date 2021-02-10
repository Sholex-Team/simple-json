#include <valarray>
#include "types/json_merge_patch.h"

namespace simple_json::types {
    Json apply_merge_patch(Json target_json, const Json &merge_patch) {
        if (merge_patch.type() == DataType::json_object_type) {
            if (target_json.type() != DataType::json_object_type) {
                target_json = Json (DataType::json_object_type);
            }
            for (auto &[key, value]: merge_patch.items()) {
                if (value.type() == DataType::null_type) {
                    if (merge_patch.find(key) != merge_patch.cend()) {
                        target_json.erase(key);
                    }
                } else {
                    target_json[key] = apply_merge_patch(target_json[key], value);
                }
            }
        } else {
            return merge_patch;
        }
        return target_json;
    }
}