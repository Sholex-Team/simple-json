#ifndef SIMPLE_JSON_JSON_PATCH_H
#define SIMPLE_JSON_JSON_PATCH_H

#include <string>
#include "json_pointer.h"
#include "../json_utils.h"
#include "json.h"
#include "exceptions/invalid_index.h"
#include "exceptions/invalid_operation.h"
#include "exceptions/invalid_patch_operation.h"
#include "exceptions/failed_test.h"
#include "json_key.h"
#include <algorithm>
#include <stdexcept>

namespace simple_json::types {
    /*!
     * @brief Json Patch type class.
     *
     * This type is used to store JSON Patch data. It also provides functionalities such as applying patches on Json
     * objects.
     */
    class JsonPatch {
    private:
        Json * patch_data;

        template<typename T>
        void apply_loop(Json & json, T it, T end) {
            JsonPatch rollback_patch {};
            Json & rollback {rollback_patch.get_json()};
            Json * target_json;
            const JsonKey path_key {"path"};
            const JsonKey value_key {"value"};
            try {
                for (; it != end; ++it) {
                    const Json & patch_object {* it};
                    std::string op {static_cast<std::string>(patch_object.at("op"))};
                    const Json & json_path {patch_object.at(path_key)};
                    const JsonPointer path {static_cast<std::string>(patch_object.at(path_key))};
                    if (op == "test")  {
                        try {
                            target_json = & json.at(path);
                        } catch (const std::out_of_range &) {
                            throw exceptions::FailedTest {path, exceptions::FailedTest::Error::INVALID_PATH};
                        }
                        if (* target_json != patch_object.at(value_key)) {
                            throw exceptions::FailedTest {path};
                        }
                    } else if (op == "add") {
                        Json & parent {json.at(path.get_parent())};
                        if (parent.type() == DataType::json_object_type) {
                            parent.insert({path.get_key(), patch_object.at(value_key)});
                        } else if (parent.type() == DataType::array_type) {
                            if (path.check_ended()){
                                parent.push_back(patch_object.at(value_key));
                            } else {
                                parent.insert(
                                        parent.cbegin() + path.get_index(), patch_object.at(value_key)
                                );
                            }
                        } else {
                            throw exceptions::InvalidPointer {};
                        }
                        rollback.push_back({{"op"_json_key, "remove"}, {"path"_json_key, json_path}});
                    } else if (op == "replace") {
                        Json & parent {json.at(path.get_parent())};
                        if (parent.type() == DataType::json_object_type || parent.type() == DataType::array_type) {
                            rollback.push_back({
                                {"op"_json_key, "replace"},
                                {"path"_json_key, json_path},
                                {"value"_json_key, json.at(path)}
                            });
                            if (parent.type() == DataType::json_object_type) {
                                parent.at(path.get_key()) = patch_object.at(value_key);
                                continue;
                            }
                            parent.at(path.get_index()) = patch_object.at(value_key);
                            continue;
                        }
                        throw exceptions::InvalidPointer {};
                    } else if (op == "remove") {
                        Json & parent {json.at(path.get_parent())};
                        if (parent.type() == DataType::array_type || parent.type() == DataType::array_type) {
                            rollback.push_back({
                                {"op"_json_key, "add"},
                                {"path"_json_key, json_path},
                                {"value"_json_key, json.at(path)}
                            });
                            if (parent.type() == DataType::json_object_type) {
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
                        if (parent.type() == DataType::array_type) {
                            size_t target_index = path.get_index();
                            if (target_index < parent.size()) {
                                throw exceptions::InvalidPointer {};
                            } else if (target_index == parent.size()) {
                                rollback.push_back({
                                    {"op"_json_key, "rm"}, {"path"_json_key, json_path}
                                });
                            } else {
                                rollback.push_back({
                                   {"op"_json_key, "replace"},
                                   {"path"_json_key, json_path},
                                   {"value"_json_key, parent.at(path)}
                                });
                            }
                            if (from_parent.type() == DataType::array_type) {
                                parent.insert(
                                        parent.cbegin() + target_index,
                                        from_parent.at(from_path.get_index())
                                );
                                continue;
                            }
                            if (from_parent.type() == DataType::json_object_type) {
                                parent.insert(
                                        parent.cbegin() + target_index,
                                        from_parent.at(from_path.get_key())
                                );
                                continue;
                            }
                        }
                        if (parent.type() == DataType::json_object_type) {
                            if (parent.find(from_path.get_key()) == parent.end()) {
                                rollback.push_back({
                                    {"op"_json_key, "rm"}, {"path"_json_key, json_path}
                                });
                            } else {
                                rollback.push_back({
                                    {"op"_json_key, "replace"},
                                    {"path"_json_key, json_path},
                                    {"value"_json_key, parent.at(path)}
                                });
                            }
                            if (from_parent.type() == DataType::array_type) {
                                parent.at(path.get_key()) = from_parent.at(from_path.get_index());
                                continue;
                            }
                            if (from_parent.type() == DataType::json_object_type) {
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
                        if (parent.type() == DataType::array_type) {
                            if (from_parent.type() == DataType::array_type) {
                                Json tmp (parent.at(from_path.get_index()));
                                from_parent.erase(from_path.get_index());
                                parent.insert(parent.cbegin() + path.get_index(), tmp);
                            } else if (from_parent.type() == DataType::json_object_type) {
                                parent.insert(
                                        parent.cbegin() + path.get_index(),
                                        from_parent.at(from_path.get_key())
                                );
                                from_parent.erase(from_path.get_key());
                            } else {
                                throw exceptions::InvalidPointer {};
                            }
                        } else if (parent.type() == DataType::json_object_type) {
                            if (from_parent.type() == DataType::array_type) {
                                parent.at(path.get_key()) = from_parent.at(from_path.get_index());
                                from_parent.erase(from_path.get_index());
                            } else if (from_parent.type() == DataType::json_object_type) {
                                parent.insert(
                                        {path.get_key(), from_parent.at(from_path.get_key())}
                                );
                                from_parent.erase(from_path.get_key());
                            } else {
                                throw exceptions::InvalidPointer {};
                            }
                        } else {
                            throw exceptions::InvalidPointer {};
                        }
                        rollback.push_back({
                            {"op"_json_key, "move"},
                            {"path"_json_key, json_from_path},
                            {"from"_json_key, json_path}
                        });
                    } else {
                        throw exceptions::InvalidPatchOperation {};
                    }
                }
            } catch (const std::exception &) {
                rollback_patch.apply(json, true);
                throw;
            }
        }

    public:
        // Constructors
        /*!
         * @brief JsonPatch default constructor.
         *
         * This constructor creates an empty JsonPatch object.
         */
        JsonPatch();

        /*!
         * @brief JsonPatch Json constructor.
         *
         * This constructor accepts a Json object as an argument and creates a JsonPatch from it.
         */
        explicit JsonPatch(const Json &);

        /*!
         * @brief JsonPatch copy constructor.
         *
         * JsonPatch copy constructor which creates a new JsonPatch based on another JsonPatch.
         * @param json_patch JsonPatch object which is about to get copied.
         */
        JsonPatch(const JsonPatch & json_patch);

        /*!
         * @brief JsonPatch move constructor.
         *
         * JsonPatch move constructor moves an already existing JsonPatch object into a new one.
         * @param json_patch JsonPatch object which is about to get moved.
         */
        JsonPatch(JsonPatch && json_patch) noexcept;

        // Destructors
        /*!
         * @brief JsonPatch destructor.
         *
         * This destructor deletes patch_data private property which is storing a Json object representing a JSON Patch.
         */
        ~JsonPatch();

        // Public Method
        /*!
         * @brief Public apply method.
         *
         * This public method can be used to apply a patch on an already existing Json object.
         * @param json [out] A reference Json object which is about to get patched.
         */
        void apply(Json & json, bool reverse = false);

        /*!
         * @brief Returns the JSON Patch data.
         *
         * This public method returns the Json object which is storing the patch data.
         * @return Json object holding the patch data.
         */
        Json & get_json() const;

        // Builders
        class PatchBuilder {
        private:
            // Private Properties
            JsonPatch * new_patch {};
            Json * dst;
            Json * current_src;
            Json * current_dst;

            // Private Methods
            template<typename T>
            void do_compare(T i, const JsonPointer & new_path, DataType used_type) {
                Json * old_src {current_src};
                Json * old_dst {current_dst};
                current_src = & current_src->at(i);
                current_dst = & current_dst->at(i);
                if (used_type == DataType::array_type) {
                    compare_array(new_path);
                } else {
                    compare_json_object(new_path);
                }
                current_src = old_src;
                current_dst = old_dst;
            }

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

/*! @example getdiff_jsonpatch.cpp
 * @brief Creating a JsonPatch object from two Json objects.
 */

/*! @example apply_jsonpatch.cpp
 * @brief Applies a JsonPatch on a Json object.
 */

#endif //SIMPLE_JSON_JSON_PATCH_H
