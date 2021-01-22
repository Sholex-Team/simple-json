#include "types/json_patch.h"

namespace simple_json::types {

    #pragma region Constructors

    JsonPatch::JsonPatch() : patch_data {new Json {}} {};

    JsonPatch::JsonPatch(const Json & json_patch) : patch_data {new Json {json_patch}} {}

    JsonPatch::JsonPatch(const JsonPatch & json_patch) : patch_data {new Json {* json_patch.patch_data}} {}

    JsonPatch::JsonPatch(JsonPatch && json_patch) noexcept : patch_data {json_patch.patch_data} {
        json_patch.patch_data = nullptr;
    }

    JsonPatch::PatchBuilder::PatchBuilder(const Json & src, const Json & dst) : src {new Json(src)},
    dst {new Json(dst)}, current_src {this->src}, current_dst {this->dst} {}

    #pragma endregion

    #pragma region Destructors

    JsonPatch::~JsonPatch() {
        delete patch_data;
    }

    JsonPatch::PatchBuilder::~PatchBuilder() {
        delete new_patch;
        delete src;
        delete dst;
    }

    #pragma endregion

    #pragma region Public Methods

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

    JsonPatch JsonPatch::PatchBuilder::create_patch() {
        if ((src->type() != DataType::json_object_type && src->type() != DataType::array_type) ||
        (dst->type() != DataType::json_object_type && dst->type() != DataType::array_type) ||
        (src->type() != dst->type())) {
            replace_item(JsonPointer {"/"}, * dst);
            return * new_patch;
        }
        if (src->type() == DataType::array_type) {
            compare_array(JsonPointer {"/"});
        } else {
            compare_json_object(JsonPointer {"/"});
        }
        return * new_patch;
    }

    #pragma endregion

    #pragma region Private Methods

    void JsonPatch::PatchBuilder::compare_array(const JsonPointer & path) {
        if (current_src->size() == current_dst->size() && * current_src == * current_dst) {
            return;
        }
        for (size_t i {current_dst->size()}; i < current_src->size(); ++i) {
            if (current_dst->find(current_src->at(i)) == current_src->end()) {
                remove_item(path + i);
            }
        }
        for (size_t i {current_src->size()}; i < current_dst->size(); ++i) {
            if (current_src->find(current_dst->at(i)) == current_dst->end()) {
                add_item(path + i, current_dst->at(i));
            }
        }
        for (size_t i {0}; i < current_src->size(); ++i) {
            if (current_src->at(i) == current_dst->at(i)) {
                continue;
            }
            if (current_dst->find(current_src->at(i)) == current_dst->end()) {
                if (current_dst->at(i).type() == current_src->at(i).type()) {
                    compare_array(path + i);
                    continue;
                }
                replace_item(path + i, current_dst->at(i));
                continue;
            }
            move_item(path + i, path + current_dst->find_index(current_dst->at(i)));
        }
    }

    void JsonPatch::PatchBuilder::remove_item(const JsonPointer & path) {
        current_src->erase(path);
        new_patch->patch_data->push_back({
            {"op"_json_key, "remove"},
            {"path"_json_key, std::string {path}}
        });
    }

    void JsonPatch::PatchBuilder::add_item(const JsonPointer & path, const Json & item) {
        if (current_src->type() == DataType::array_type) {
            current_src->insert(current_src->get_item(path.get_index()), item);
        } else {
            current_src->at(path) = item;
        }
        new_patch->patch_data->push_back({
            {"op"_json_key, "add"},
            {"path"_json_key, std::string {path}},
            {"value"_json_key, item}
        });
    }

    void JsonPatch::PatchBuilder::replace_item(const JsonPointer & path, const Json & item) {
        current_src->at(path) = item;
        new_patch->patch_data->push_back({
            {"op"_json_key, "replace"},
            {"path"_json_key, std::string {path}},
            {"value"_json_key, item}
        });
    }

    void JsonPatch::PatchBuilder::move_item(const JsonPointer & old_path, const JsonPointer & new_path) {
        if (current_src->type() == DataType::array_type) {
            Json::const_iterator from {current_src->get_item(old_path.get_index())};
            std::rotate(from, from + 1, current_src->get_item(new_path.get_index()) + 1);
        } else {
            current_src->at(new_path) = std::move(current_src->at(old_path));
            current_src->erase(old_path);
        }
        new_patch->patch_data->push_back({
            {"op"_json_key, "move"},
            {"from"_json_key, std::string {old_path}},
            {"path"_json_key, std::string {new_path}}
        });
    }

    #pragma endregion
}
