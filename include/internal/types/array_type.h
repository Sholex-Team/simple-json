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
         * @brief Array list initializer constructor.
         *
         * This constructor takes an initializer list containing Json objects and creates an Array from it.
         * @param initializer_list Initializer list containing Json objects.
         */
        Array(const array_list_type & initializer_list);

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const Array & array);
        friend JsonObject;
    };

    /*!
     * @relatedalso Array
     * @brief Array stream insertion operator.
     *
     * This Array stream insertion overloaded operator provides the ability to serialize Array object and insert it into
     * the stdout stream.
     * @param os [out] Output Stream
     * @param array [in] Array which is going to get serialized.
     * @return A reference to the Output Stream(os)
     */
    std::ostream & operator<<(std::ostream & os, const Array & array);
}

#endif //SIMPLE_JSON_ARRAY_TYPE_H
