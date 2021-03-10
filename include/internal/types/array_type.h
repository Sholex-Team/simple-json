#ifndef SIMPLE_JSON_ARRAY_TYPE_H
#define SIMPLE_JSON_ARRAY_TYPE_H

#include <vector>
#include <ostream>
#include "../indent.h"
#include <iomanip>

namespace simple_json::types {
    class Json;
    class JsonObject;
    using type_array = std::vector<Json>;
    using array_list_type = std::initializer_list<Json>;

    /*!
     * @brief Array type.
     *
     * This type is used inside a Json object representing a JSON Array.
     * Array type is derived from std::vector<Json>.
     */
    class Array : public type_array {
    private:
        std::ostream & stream_without_indent(std::ostream & os) const;
        std::ostream & stream_with_indent(std::ostream & os, size_t indent_size) const;
    public:
        // Constructors
        /*!
         * @brief Array default constructor.
         *
         * This constructor is derived from std::vector<Json>.
         */
        Array() = default;

        /*!
         * @brief Array copy constructor.
         *
         * Array copy constructor derived from std::vector<Json> copy constructor.
         * @param array Array which is going to be copied.
         */
        Array(const Array & array) = default;

        /*!
         * @brief Array move constructor.
         *
         * Array move constructor derived from std::vector<Json> move constructor.
         * @param array Array which is about to be moved.
         */
        Array(Array && array) noexcept = default;

        /*!
         * @brief Array list initializer constructor.
         *
         * This constructor takes a list initializer containing Json objects and creates an Array from it.
         * @param list_initial List Initializer containing Json objects.
         */
        Array(const array_list_type & list_initial);

        // Assignment Operator Overloading
        /*!
         * @brief Array copy assignment operator.
         *
         * This overloaded copy assignment operator copies an Array object into existing LHS Array object.
         * @param array Array object which is about to be copied.
         * @return A reference to current Array object.
         */
        Array & operator=(const Array & array) = default;

        /*!
         * @brief Array move assignment operator.
         *
         * This overloaded copy assignment moves an Array object into existing LHS Array object.
         * @param array Array object which is about to be moved.
         * @return A reference to current Array object.
         */
        Array & operator=(Array && array) noexcept = default;

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const Array & array);
        friend JsonObject;
    };

    /*!
     * @brief Array stream insertion operator.
     *
     * This Array stream insertion overloaded operator provides the ability to serialize Array object and insert it into
     * the stdout stream.
     * @param os[out] Output Stream.
     * @param array[in] Array which is going to get serialized.
     * @return A reference to the Output Stream(os).
     */
    std::ostream & operator<<(std::ostream & os, const Array & array);
}

#endif //SIMPLE_JSON_ARRAY_TYPE_H
