#include "types/json.h" // TODO

namespace simple_json::types {

    JsonPatch::JsonPatch(const Json & json_patch) : patch {new Json {json_patch}} {}

    JsonPatch::JsonPatch(const JsonPatch & json_patch) : patch {new Json {*json_patch.patch}} {}

    JsonPatch::JsonPatch(JsonPatch && json_patch) noexcept : patch {json_patch.patch} {
        json_patch.patch = nullptr;
    }

    JsonPatch::~JsonPatch() {
        delete patch;
    }

    void JsonPatch::action(Json & json) {
        for (Json patch_object: * patch) {
            if (patch_object.at("op") == "add") {
                std::string path {static_cast<std::string>(patch_object.at("path"))};
                size_t pos {path.rfind('/')};
                JsonPointer target_pointer {path.substr(0, path.size() - pos)};
                std::string last_index {path.substr(pos)};
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
                    target_json[last_index] = patch_object.at("value");
                } else {
                    throw; // TODO
                }
            }
        }
    }
}
