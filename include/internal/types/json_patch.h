
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
        void apply(Json & json);

        /*!
         * @brief Returns the JSON Patch data.
         *
         * This public method returns the Json object which is storing the patch data.
         * @return Json object holding the patch data.
         */
        const Json & get_json() const;

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
