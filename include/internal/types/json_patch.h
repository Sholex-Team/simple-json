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
        // Private Properties
        Json * patch_data;

        // Private Methods
        template<typename T>
        void apply_loop(Json &json, T begin, T end);

    public:
        // Constructors
        /*!
         * @brief JsonPatch default constructor
         *
         * This constructor creates an empty JsonPatch object.
         */
        [[nodiscard]] JsonPatch();

        /*!
         * @brief JsonPatch Json constructor
         *
         * This constructor accepts a Json object as an argument and creates a JsonPatch from it.
         */
        [[nodiscard]] explicit JsonPatch(const Json &);

        /*!
         * @brief JsonPatch copy constructor
         * @param json_patch JsonPatch object which is about to get copied.
         */
        [[nodiscard]] JsonPatch(const JsonPatch & json_patch);

        /*!
         * @brief JsonPatch move constructor
         * @param json_patch JsonPatch object which is about to get moved.
         */
        [[nodiscard]] JsonPatch(JsonPatch && json_patch) noexcept;

        // Destructors
        ~JsonPatch();

        // Public Method
        /*!
         * @brief Applies the JsonPatch on the Json object passed into the method.
         * @param json [out] A reference to the Json object which is about to get patched.
         * @throw exceptions::InvalidPointer Throws when one of the patch JSON Pointers is invalid.
         * @throw exceptions::FailedTest Throws when a JSON Patch test fails.
         * @throw exceptions::InvalidPatchOperation Throws when the patch contains an invalid operation.
         * @param reverse If true is passed, method will apply the patch in reverse order.
         */
        void apply(Json & json, bool reverse = false);

        /*!
         * @brief Returns the JSON Patch data.
         *
         * This public method returns the Json object which is storing the patch data.
         * @return Json object holding the patch data.
         */
        [[nodiscard]] Json & get_json() const;

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
            void do_compare(T i, const JsonPointer &new_path, DataType used_type);
            void compare_array(const JsonPointer & path);
            void compare_json_object(const JsonPointer & path);
            void remove_item(const JsonPointer & path);
            void add_item(const JsonPointer & path, const Json & item);
            void replace_item(const JsonPointer & path, const Json & item);
            void move_item(const JsonPointer & old_path, const JsonPointer & new_path);
        public:
            // Constructor
            [[nodiscard]] PatchBuilder(const Json & src, const Json & dst);

            // Destructor
            ~PatchBuilder();

            // Public Methods
            [[nodiscard]] JsonPatch create_patch();
        };

        // Friends
        friend class PatchBuilder;
    };
}

/*! @example getdiff_jsonpatch.cpp
 * @brief Creating a JsonPatch object from two Json objects.
 */

/*! @example apply_jsonpatch.cpp
 * @brief Applies a JsonPatch on a Json object.
 */

#endif //SIMPLE_JSON_JSON_PATCH_H
