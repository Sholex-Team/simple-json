#include "types/json_patch.h"

namespace simple_json::types {
    JsonPatch::JsonPatch(const Json & json_patch) : patch_data {new Json {json_patch}} {}

    JsonPatch::JsonPatch(const JsonPatch & json_patch) : patch_data {new Json {* json_patch.patch_data}} {}

    JsonPatch::JsonPatch(JsonPatch && json_patch) noexcept : patch_data {json_patch.patch_data} {
        json_patch.patch_data = nullptr;
    }

    JsonPatch::~JsonPatch() {
        delete patch_data;
    }

    void JsonPatch::patch(Json & json) {
        for (Json & patch_object: * patch_data) {
            if (patch_object.at("op") == "add") {
                std::string path {patch_object.at("path")};
                size_t pos {path.rfind('/')};
                JsonPointer target_pointer {path.substr(0, pos)};
                std::string last_index {path.substr(pos + 1)};
                Json & target_json {json[target_pointer]};
                if (target_json.used_type == DataType::array_type) {
                    if (last_index == "-") {
                        target_json.push_back(patch_object.at("value"));
                    } else if (utils::is_digit(last_index)) {
                        target_json.data_array->insert(
                                target_json.data_array->begin() + strtol(last_index.c_str(), nullptr, 10),
                                patch_object.at("value")
                                );

                    } else {
                        throw; // TODO
                    }
                } else if (target_json.used_type == DataType::json_object_type){
                    target_json.data_json_object->emplace(JsonKey {last_index}, patch_object.at("value"));
                } else {
                    throw; // TODO
                }
            } else if (patch_object.at("op") == "remove")  {
                std::string path {patch_object.at("path")};
                size_t pos {path.rfind('/')};
                JsonPointer target_pointer {path.substr(0, path.size() - pos - 1)};
                std::string last_index {path.substr(pos)};
                Json & target_json {json[target_pointer]};
                if (target_json.used_type == DataType::array_type) {
                    if (utils::is_digit(last_index)) {
                        target_json.data_array->erase(
                                target_json.data_array->begin() +
                                strtol(last_index.c_str(), nullptr, 10)
                        );

                    } else {
                        throw; // TODO
                    }
                } else if (target_json.used_type == DataType::json_object_type){
                    target_json.data_json_object->erase(JsonKey {last_index});
                } else {
                    throw; // TODO
                }
            }
        }
    }
}
