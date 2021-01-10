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
                        continue;
                    } else if (utils::is_digit(last_index)) {
                        target_json.data_array->insert(target_json.data_array->begin() + strtol(
                                last_index.c_str(), nullptr, 10
                                ),patch_object.at("value"));
                        continue;
                    }
                    throw exceptions::InvalidIndexException {};
                } else if (target_json.used_type == DataType::json_object_type){
                    target_json.data_json_object->emplace(JsonKey {last_index}, patch_object.at("value"));
                    continue;
                }
                throw exceptions::InvalidOperation {};
            } else if (patch_object.at("op") == "remove")  {
                json.erase(JsonPointer {static_cast<std::string>(patch_object.at("path"))});
                continue;
            } else if (patch_object.at("op") == "replace") {
                std::string path {patch_object.at("path")};
                size_t pos {path.rfind('/')};
                JsonPointer target_pointer {path.substr(0, path.size() - pos - 1)};
                std::string last_index {path.substr(pos)};
                Json & target_json {json[target_pointer]};
                if (target_json.used_type == DataType::array_type) {
                    if (utils::is_digit(last_index)) {
                        target_json.data_array->at(strtol(last_index.c_str(), nullptr, 10)) = patch_object.at("value");
                        continue;
                    }
                    throw exceptions::InvalidIndexException {patch_object.used_type};
                } else if (target_json.used_type == DataType::json_object_type) {
                    target_json.data_json_object->at(JsonKey {last_index}) = patch_object.at("value");
                    continue;
                }
                throw exceptions::InvalidOperation {};
            } else if (patch_object.at("op") == "test") {
                if (json.at(
                        JsonPointer {static_cast<std::string>(patch_object.at("path"))}
                        ) == patch_object.at("value")) {
                    continue;
                }
                throw exceptions::FailedTest {};
            } else if (patch_object.at("op") == "copy") {
                json[
                        JsonPointer {static_cast<std::string>(patch_object.at("from"))}
                        ] = json.at(JsonPointer {static_cast<std::string>(patch_object.at("path"))});
            } else if (patch_object.at("op") == "move") {
                json[
                        JsonPointer {static_cast<std::string>(patch_object.at("from"))}
                        ] = json.at(JsonPointer {static_cast<std::string>(patch_object.at("path"))});
                json.erase(JsonPointer {static_cast<std::string>(patch_object.at("path"))});
            }
        }
    }
}
