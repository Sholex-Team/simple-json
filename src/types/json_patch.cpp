#include "types/json_patch.h"

namespace simple_json::types {

    #pragma region Constructors

    JsonPatch::JsonPatch() : patch_data {new Json(DataType::array_type)} {}

    JsonPatch::JsonPatch(const Json & json_patch) : patch_data {new Json(json_patch)} {}

    JsonPatch::JsonPatch(const JsonPatch & json_patch) : patch_data {new Json(* json_patch.patch_data)} {}

    JsonPatch::JsonPatch(JsonPatch && json_patch) noexcept : patch_data {json_patch.patch_data} {
        json_patch.patch_data = nullptr;
    }

    JsonPatch::PatchBuilder::PatchBuilder(const Json & src, const Json & dst) : new_patch {new JsonPatch {}},
    dst {new Json(dst)}, current_src {new Json(src)}, current_dst {this->dst} {}

    #pragma endregion

    #pragma region Destructors

    JsonPatch::~JsonPatch() {
        delete patch_data;
    }

    JsonPatch::PatchBuilder::~PatchBuilder() {
        delete new_patch;
        delete current_src;
        delete dst;
    }

    #pragma endregion

    #pragma region Public Methods

    const Json & JsonPatch::get_json() const {
        return * patch_data;
    }

    void JsonPatch::apply(Json & json) {
        for (Json & patch_object: * patch_data) {
            std::string op {static_cast<std::string>(patch_object.at("op"))};
            JsonPointer path {static_cast<std::string>(patch_object.at("path"))};
            if (op == "test")  {
                if (json.at(path) != patch_object.at("value")) {
                    throw exceptions::FailedTest {};
                }
            } else if (op == "add") {
                Json & parent {json.at(path.get_parent())};
                if (parent.type() == DataType::json_object_type) {
                    parent.insert({path.get_key(), patch_object.at("value")});
                } else if (parent.type() == DataType::array_type) {
                    parent.insert(parent.cbegin() + path.get_index(), patch_object.at("value"));
                } else {
                    throw exceptions::InvalidPointer {};
                }
            } else if (op == "replace") {
                Json & parent {json.at(path.get_parent())};
                if (parent.type() == DataType::json_object_type) {
                    parent.at(path.get_key()) = patch_object.at("value");
                } else if (parent.type() == DataType::array_type) {
                    parent.at(path.get_index()) = patch_object.at("value");
                } else {
                    throw exceptions::InvalidPointer {};
                }
            } else if (op == "remove") {
                Json & parent {json.at(path.get_parent())};
                if (parent.type() == DataType::json_object_type) {
                    parent.erase(path.get_key());
                } else if (parent.type() == DataType::array_type) {
                    parent.erase(path.get_index());
                } else {
                    throw exceptions::InvalidPointer {};
                }
            } else if (op == "copy") {
                JsonPointer from_path {static_cast<std::string>(patch_object.at("from"))};
                Json & parent_path {json.at(path.get_parent())};
                Json & parent_from {json.at(from_path.get_parent())};
                if (parent_path.type() == DataType::array_type) {
                    if (parent_from.type() == DataType::array_type) {
                        parent_path.insert(parent_path.cbegin() + path.get_index(), parent_from.at(from_path.get_index()));
                    } else {
                        parent_path.insert(parent_path.cbegin() + path.get_index(), parent_from.at(from_path.get_key()));
                    }
                } else {
                    if (parent_from.type() == DataType::array_type) {
                        parent_path.at(path.get_index()) = parent_from.at(from_path.get_index());
                    } else {
                        parent_path.at(path.get_index()) = parent_from.at(from_path.get_key());
                    }
                }
            } else if (op == "move") {
                JsonPointer from_path {static_cast<std::string>(patch_object.at("from"))};
                Json & parent_path {json.at(path.get_parent())};
                Json & parent_from {json.at(from_path.get_parent())};
                if (parent_path.type() == DataType::array_type) {
                    if (parent_from.type() == DataType::array_type) {
                        Json tmp (parent_path.at(from_path.get_index()));
                        parent_from.erase(from_path.get_index());
                        parent_path.insert(parent_path.cbegin() + path.get_index(), tmp);
                    } else {
                        parent_path.insert(parent_path.cbegin() + path.get_index(), parent_from.at(from_path.get_key()));
                        parent_from.erase(from_path.get_key());
                    }
                } else {
                    if (parent_from.type() == DataType::array_type) {
                        parent_path.at(path.get_key()) = parent_from.at(from_path.get_index());
                        parent_from.erase(from_path.get_index());
                    } else {
                        parent_path.insert(parent_path.cbegin() + path.get_index(), parent_from.at(from_path.get_key()));
                        parent_from.erase(from_path.get_key());
                    }
                }
            } else {
                throw exceptions::InvalidOperation {};
            }
        }
    }

    JsonPatch JsonPatch::PatchBuilder::create_patch() {
        if ((current_src->type() != DataType::json_object_type && current_src->type() != DataType::array_type) ||
        (dst->type() != DataType::json_object_type && dst->type() != DataType::array_type) ||
        (current_src->type() != dst->type())) {
            replace_item(JsonPointer {"/"}, * dst);
            return * new_patch;
        }
        if (current_src->type() == DataType::array_type) {
            compare_array(JsonPointer {"/"});
        } else if (current_src->type() == DataType::json_object_type) {
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
            Json & current_item {current_src->at(i)};
            if (current_dst->count_in_range(current_dst->cbegin() + i, current_dst->cend(), current_item)
            < current_src->count_in_range(current_src->cbegin() + i, current_src->cend(), current_item)) {
                remove_item(path + i);
                --i;
            }
        }
        for (size_t i {current_src->size()}; i < current_dst->size(); ++i) {
            Json & current_item {current_dst->at(i)};
            if (current_src->count_in_range(current_src->cbegin() + i, current_src->cend(), current_item)
            < current_dst->count_in_range(current_dst->cbegin() + i, current_dst->cend(), current_item)) {
                add_item(path + i, current_item);
            }
        }
        for (size_t i {0}; i < current_src->size(); ++i) {
            Json & current_item {current_src->at(i)};
            if (current_item == current_dst->at(i)) {
                continue;
            }
            Json::const_iterator current_target {current_dst->cbegin() + i};
            for (Json::const_iterator it {current_src->cbegin() + i};
            current_target != current_dst->cend();
            ++it, ++current_target) {
                if (current_item == * current_target && * current_target != * it) {
                    break;
                }
            }
            if (current_target == current_dst->cend()) {
                if (current_dst->at(i).type() == DataType::array_type &&
                current_src->at(i).type() == DataType::array_type) {
                    do_compare(i, path + i, DataType::array_type);
                    continue;
                } else if (current_dst->at(i).type() == DataType::json_object_type &&
                           current_src->at(i).type() == DataType::json_object_type) {
                    do_compare(i, path + i, DataType::json_object_type);
                    continue;
                }
                replace_item(path + i, current_dst->at(i));
                continue;
            }
            move_item(path + i, path + current_dst->find_index(current_target));
            --i;
        }
    }

    void JsonPatch::PatchBuilder::compare_json_object(const JsonPointer & path) {
        if (current_src->size() == current_dst->size() && * current_src == * current_dst) {
            return;
        }
        for (Json::const_iterator it {current_src->cbegin()}; it != current_src->cend(); ++it) {
            if (current_dst->find(it.key()) != current_dst->end()) {
                if (current_dst->at(it.key()) == it.value()) {
                    dst->erase(path + it.key());
                    continue;
                } else if (current_dst->at(it.key()).type() == DataType::array_type &&
                           current_src->at(it.key()).type() == DataType::array_type) {
                    do_compare(it.key(), path + it.key(), DataType::array_type);
                    dst->erase(path + it.key());
                    continue;
                } else if (current_dst->at(it.key()).type() == DataType::json_object_type &&
                           current_src->at(it.key()).type() == DataType::json_object_type) {
                    do_compare(it.key(), path + it.key(), DataType::json_object_type);
                    dst->erase(path + it.key());
                    continue;
                } else {
                    replace_item(path + it.key(), current_dst->at(it.key()));
                }
            } else {
                Json::iterator target_it{current_dst->find(it.value())};
                if (target_it != current_dst->end()) {
                    move_item(path + it.key(), path + target_it.key());
                    continue;
                }
                remove_item(path + it.key());
            }
        }
        for (Json::const_iterator it {current_dst->cbegin()}; it != current_dst->cend(); ++it) {
            add_item(path + it.key(), it.value());
        }
    }

    void JsonPatch::PatchBuilder::remove_item(const JsonPointer & path) {
        if (current_src->type() == DataType::array_type) {
            current_src->erase(path.get_index());
        }
        new_patch->patch_data->push_back({
            {"op"_json_key, "remove"},
            {"path"_json_key, static_cast<std::string>(path)}
        });
    }

    void JsonPatch::PatchBuilder::add_item(const JsonPointer & path, const Json & item) {
        if (current_src->type() == DataType::array_type) {
            current_src->insert(current_src->get_item(path.get_index()), item);
        }
        new_patch->patch_data->push_back({
            {"op"_json_key, "add"},
            {"path"_json_key, static_cast<std::string>(path)},
            {"value"_json_key, item}
        });
    }

    void JsonPatch::PatchBuilder::replace_item(const JsonPointer & path, const Json & item) {
        if (current_src->type() == DataType::array_type) {
            current_src->at(path.get_index()) = item;
        } else {
            dst->erase(path);
        }
        new_patch->patch_data->push_back({
            {"op"_json_key, "replace"},
            {"path"_json_key, static_cast<std::string>(path)},
            {"value"_json_key, item}
        });
    }

    void JsonPatch::PatchBuilder::move_item(const JsonPointer & old_path, const JsonPointer & new_path) {
        if (current_src->type() == DataType::array_type) {
            Json temp(std::move(current_src->at(old_path.get_index())));
            current_src->erase(old_path.get_index());
            current_src->insert(current_src->get_item(new_path.get_index()), std::move(temp));
        } else {
            dst->erase(new_path);
        }
        new_patch->patch_data->push_back({
            {"op"_json_key, "move"},
            {"from"_json_key, static_cast<std::string>(old_path)},
            {"path"_json_key, static_cast<std::string>(new_path)}
        });
    }

#pragma endregion
}
