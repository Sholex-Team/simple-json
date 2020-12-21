#include "array_type.h"
#include "json.h"


namespace simple_json::types {
    using namespace indent;
    #pragma region Construcors

    Array::Array(const array_list_type & list_initial) : type_array(list_initial) {}

    #pragma endregion

    #pragma region OS Overloading

    std::ostream & operator<<(std::ostream & os, const Array & array) {
        if (indent_length == 0) {
            return array.stream_without_indent(os);
        }
        return array.stream_with_indent(os, indent_length);
    }

    #pragma endregion

    #pragma region Private Methods

    std::ostream & Array::stream_without_indent(std::ostream & os) const {
        os << '[';
        for (const Json & item: * this) {
            os << item << ( item == *std::prev(end()) ? "" : ", ");
        }
        os << ']';
        return os;
    }

    std::ostream & Array::stream_with_indent(std::ostream & os, size_t local_indent) const {
        os << '[';
        for (const Json & item: * this) {
            os << std::endl;
            os << std::setw(local_indent);
            switch (item.used_type) {
                case DataType::json_object_type:
                    item.data_json_object->stream_with_indent(os, local_indent + indent_length);
                    break;
                case DataType::array_type:
                    item.data_array->stream_with_indent(os, local_indent + indent_length);
                    break;
                default:
                    os << item;
            }
            os << ( item == *std::prev(end()) ? "" : ",");
        }
        os << '\n' << std::setw(local_indent - indent_length) << ']';
        return os;
    }

    #pragma endregion

}

