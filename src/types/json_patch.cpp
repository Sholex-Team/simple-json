#include "types/json_patch.h"

namespace simple_json::types {

    #pragma region Constructors

    JsonPatch::JsonPatch() : patch_data {new Json(DataType::ARRAY_TYPE)} {}

    JsonPatch::JsonPatch(const Json & json_patch) {
        json_patch.check_data(DataType::ARRAY_TYPE);
        patch_data = new Json(json_patch);
    }

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

    Json & JsonPatch::get_json() const {
        return * patch_data;
    }

    void JsonPatch::apply(Json & json, bool reverse) {
        if (json.empty()) {
            return;
        }
        if (reverse)
            apply_loop<Json::const_reverse_iterator>(json, patch_data->crbegin(), patch_data->crend());
        else
            apply_loop<Json::const_iterator>(json, patch_data->cbegin(), patch_data->cend());
    }

    JsonPatch JsonPatch::PatchBuilder::create_patch() {
        if ((current_src->type() != DataType::JSON_OBJECT_TYPE && current_src->type() != DataType::ARRAY_TYPE) ||
            (dst->type() != DataType::JSON_OBJECT_TYPE && dst->type() != DataType::ARRAY_TYPE) ||
            (current_src->type() != dst->type())) {
            replace_item(JsonPointer {"/"}, * dst);
            return * new_patch;
        }
        if (current_src->type() == DataType::ARRAY_TYPE) {
            compare_array(JsonPointer {"/"});
        } else if (current_src->type() == DataType::JSON_OBJECT_TYPE) {
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
            if (current_dst->count_in_range<Json::const_iterator>(
                    current_dst->cbegin() + i, current_dst->cend(), current_item)
            < current_src->count_in_range<Json::const_iterator>(
                    current_src->cbegin() + i, current_src->cend(), current_item)) {
                remove_item(path + i);
                --i;
            }
        }
        for (size_t i {current_src->size()}; i < current_dst->size(); ++i) {
            Json & current_item {current_dst->at(i)};
            if (current_src->count_in_range<Json::const_iterator>(
                    current_src->cbegin() + i, current_src->cend(), current_item)
            < current_dst->count_in_range<Json::const_iterator>(
                    current_dst->cbegin() + i, current_dst->cend(), current_item)) {
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
                if (current_dst->at(i).type() == DataType::ARRAY_TYPE &&
                current_src->at(i).type() == DataType::ARRAY_TYPE) {
                    do_compare(i, path + i, DataType::ARRAY_TYPE);
                    continue;
                } else if (current_dst->at(i).type() == DataType::JSON_OBJECT_TYPE &&
                           current_src->at(i).type() == DataType::JSON_OBJECT_TYPE) {
                    do_compare(i, path + i, DataType::JSON_OBJECT_TYPE);
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
                } else if (current_dst->at(it.key()).type() == DataType::ARRAY_TYPE &&
                           current_src->at(it.key()).type() == DataType::ARRAY_TYPE) {
                    do_compare(it.key(), path + it.key(), DataType::ARRAY_TYPE);
                    dst->erase(path + it.key());
                    continue;
                } else if (current_dst->at(it.key()).type() == DataType::JSON_OBJECT_TYPE &&
                           current_src->at(it.key()).type() == DataType::JSON_OBJECT_TYPE) {
                    do_compare(it.key(), path + it.key(), DataType::JSON_OBJECT_TYPE);
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
        if (current_src->type() == DataType::ARRAY_TYPE) {
            current_src->erase(path.get_index());
        }
        new_patch->patch_data->push_back({
            {"op"_json_key, "remove"},
            {"path"_json_key, static_cast<std::string>(path)}
        });
    }

    void JsonPatch::PatchBuilder::add_item(const JsonPointer & path, const Json & item) {
        if (current_src->type() == DataType::ARRAY_TYPE) {
            current_src->insert(current_src->get_item(path.get_index()), item);
        }
        new_patch->patch_data->push_back({
            {"op"_json_key, "add"},
            {"path"_json_key, static_cast<std::string>(path)},
            {"value"_json_key, item}
        });
    }

    void JsonPatch::PatchBuilder::replace_item(const JsonPointer & path, const Json & item) {
        new_patch->patch_data->push_back({
             {"op"_json_key, "replace"},
             {"path"_json_key, static_cast<std::string>(path)},
             {"value"_json_key, item}
        });
        if (current_src->type() == DataType::ARRAY_TYPE) {
            current_src->at(path.get_index()) = item;
        } else {
            dst->erase(path);
        }
    }

    void JsonPatch::PatchBuilder::move_item(const JsonPointer & old_path, const JsonPointer & new_path) {
        if (current_src->type() == DataType::ARRAY_TYPE) {
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

    template<typename T>
    void JsonPatch::PatchBuilder::do_compare(T i, const JsonPointer &new_path, DataType used_type) {
        Json * old_src {current_src};
        Json * old_dst {current_dst};
        current_src = & current_src->at(i);
        current_dst = & current_dst->at(i);
        if (used_type == DataType::ARRAY_TYPE)
            compare_array(new_path);
        else
            compare_json_object(new_path);
        current_src = old_src;
        current_dst = old_dst;
    }

    template<typename T>
    void JsonPatch::apply_loop(Json &json, T begin, T end) {
        JsonPatch rollback_patch {};
        Json & rollback {rollback_patch.get_json()};
        Json * target_json;
        const JsonKey path_key {"path"};
        const JsonKey value_key {"value"};
        try {
            for (; begin != end; ++begin) {
                const Json & patch_object {*begin};
                std::string op {static_cast<std::string>(patch_object.at("op"))};
                const Json & json_path {patch_object.at(path_key)};
                const JsonPointer path {static_cast<std::string>(patch_object.at(path_key))};
                if (op == "test")  {
                    try {
                        target_json = & json.at(path);
                    } catch (const std::out_of_range &) {
                        throw exceptions::FailedTest {path, exceptions::FailedTest::Error::INVALID_PATH};
                    }
                    if (* target_json != patch_object.at(value_key))
                        throw exceptions::FailedTest {path};
                } else if (op == "add") {
                    Json & parent {json.at(path.get_parent())};
                    if (parent.type() == DataType::JSON_OBJECT_TYPE)
                        parent.insert({path.get_key(), patch_object.at(value_key)});
                    else if (parent.type() == DataType::ARRAY_TYPE)
                        if (path.check_ended())
                            parent.push_back(patch_object.at(value_key));
                        else
                            parent.insert(parent.cbegin() + path.get_index(), patch_object.at(value_key));
                    else
                        throw exceptions::InvalidPointer {};
                    rollback.push_back({{"op"_json_key, "remove"}, {"path"_json_key, json_path}});
                } else if (op == "replace") {
                    Json & parent {json.at(path.get_parent())};
                    if (parent.type() == DataType::JSON_OBJECT_TYPE || parent.type() == DataType::ARRAY_TYPE) {
                        rollback.push_back({{"op"_json_key, "replace"}, {"path"_json_key, json_path},
                                            {"value"_json_key, json.at(path)}});
                        if (parent.type() == DataType::JSON_OBJECT_TYPE) {
                            parent.at(path.get_key()) = patch_object.at(value_key);
                            continue;
                        }
                        parent.at(path.get_index()) = patch_object.at(value_key);
                        continue;
                    }
                    throw exceptions::InvalidPointer {};
                } else if (op == "remove") {
                    Json & parent {json.at(path.get_parent())};
                    if (parent.type() == DataType::ARRAY_TYPE || parent.type() == DataType::JSON_OBJECT_TYPE) {
                        rollback.push_back({{"op"_json_key, "add"}, {"path"_json_key, json_path},
                                            {"value"_json_key, json.at(path)}});
                        if (parent.type() == DataType::JSON_OBJECT_TYPE) {
                            parent.erase(path.get_key());
                            continue;
                        }
                        parent.erase(path.get_index());
                        continue;
                    }
                    throw exceptions::InvalidPointer {};
                } else if (op == "copy") {
                    JsonPointer from_path {static_cast<std::string>(patch_object.at("from"))};
                    Json & parent {json.at(path.get_parent())};
                    Json & from_parent {json.at(from_path.get_parent())};
                    if (parent.type() == DataType::ARRAY_TYPE) {
                        size_t target_index = path.get_index();
                        if (target_index < parent.size())
                            throw exceptions::InvalidPointer {};
                        else if (target_index == parent.size())
                            rollback.push_back({{"op"_json_key, "rm"}, {"path"_json_key, json_path}});
                        else
                            rollback.push_back({{"op"_json_key, "replace"}, {"path"_json_key, json_path},
                                                {"value"_json_key, parent.at(path)}});
                        if (from_parent.type() == DataType::ARRAY_TYPE) {
                            parent.insert(parent.cbegin() + target_index, from_parent.at(from_path.get_index()));
                            continue;
                        }
                        if (from_parent.type() == DataType::JSON_OBJECT_TYPE) {
                            parent.insert(parent.cbegin() + target_index, from_parent.at(from_path.get_key()));
                            continue;
                        }
                    }
                    if (parent.type() == DataType::JSON_OBJECT_TYPE) {
                        if (parent.find(from_path.get_key()) == parent.end())
                            rollback.push_back({{"op"_json_key, "rm"}, {"path"_json_key, json_path}});
                        else
                            rollback.push_back({{"op"_json_key, "replace"}, {"path"_json_key, json_path},
                                                {"value"_json_key, parent.at(path)}});
                        if (from_parent.type() == DataType::ARRAY_TYPE) {
                            parent.at(path.get_key()) = from_parent.at(from_path.get_index());
                            continue;
                        }
                        if (from_parent.type() == DataType::JSON_OBJECT_TYPE) {
                            parent.at(path.get_key()) = from_parent.at(from_path.get_key());
                            continue;
                        }
                        throw exceptions::InvalidPointer {};
                    }
                    throw exceptions::InvalidPointer {};
                } else if (op == "move") {
                    const Json & json_from_path {patch_object.at("from")};
                    JsonPointer from_path {static_cast<std::string>(json_from_path)};
                    Json & parent {json.at(path.get_parent())};
                    Json & from_parent {json.at(from_path.get_parent())};
                    if (parent.type() == DataType::ARRAY_TYPE)
                        if (from_parent.type() == DataType::ARRAY_TYPE) {
                            Json tmp (parent.at(from_path.get_index()));
                            from_parent.erase(from_path.get_index());
                            parent.insert(parent.cbegin() + path.get_index(), tmp);
                        } else if (from_parent.type() == DataType::JSON_OBJECT_TYPE) {
                            parent.insert( parent.cbegin() + path.get_index(), from_parent.at(from_path.get_key()));
                            from_parent.erase(from_path.get_key());
                        } else {
                            throw exceptions::InvalidPointer {};
                        }
                    else if (parent.type() == DataType::JSON_OBJECT_TYPE)
                        if (from_parent.type() == DataType::ARRAY_TYPE) {
                            parent.at(path.get_key()) = from_parent.at(from_path.get_index());
                            from_parent.erase(from_path.get_index());
                        } else if (from_parent.type() == DataType::JSON_OBJECT_TYPE) {
                            parent.insert({path.get_key(), from_parent.at(from_path.get_key())});
                            from_parent.erase(from_path.get_key());
                        } else {
                            throw exceptions::InvalidPointer {};
                        }
                    else
                        throw exceptions::InvalidPointer {};
                    rollback.push_back({{"op"_json_key, "move"}, {"path"_json_key, json_from_path},
                                        {"from"_json_key, json_path}});
                } else
                    throw exceptions::InvalidPatchOperation {};
            }
        } catch (const std::exception &) {
            rollback_patch.apply(json, true);
            throw;
        }
    }

    #pragma endregion

    #pragma region Explicit Template Instantiation

    template void JsonPatch::apply_loop<Json::iterator>(Json &, Json::iterator begin, Json::iterator end);
    template void JsonPatch::apply_loop<Json::const_iterator>(Json &, Json::const_iterator begin,
            Json::const_iterator end);
    template void JsonPatch::apply_loop<Json::reverse_iterator>(Json &, Json::reverse_iterator begin,
            Json::reverse_iterator end);
    template void JsonPatch::apply_loop<Json::const_reverse_iterator>(Json &, Json::const_reverse_iterator begin,
            Json::const_reverse_iterator end);

    template void JsonPatch::PatchBuilder::do_compare<size_t>(size_t i, const JsonPointer &, DataType);
    template void JsonPatch::PatchBuilder::do_compare<const JsonKey &>(const JsonKey &, const JsonPointer &, DataType);

    #pragma endregion
}
