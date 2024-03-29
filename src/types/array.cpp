#include "types/array.h"
#include "types/json.h"


namespace simple_json::types {
    using namespace indent;
    #pragma region Construcors

    Array::Array(const array_list_type & initializer_list) : type_array(initializer_list) {}

    #pragma endregion

    #pragma region OS Overloading

    std::ostream & operator<<(std::ostream & os, const Array & array) {
        if (indent_length == 0)
            return array.stream_without_indent(os);
        return array.stream_with_indent(os, indent_length);
    }

    #pragma endregion

    #pragma region Private Methods

    std::ostream & Array::stream_without_indent(std::ostream & os) const {
        os << '[';
        for (const Json & item: * this)
            os << ((item.type() == DataType::STRING_TYPE) ? item.serialize() : item)
            << (item == *std::prev(end()) ? "" : ", ");
        os << ']';
        return os;
    }

    std::ostream & Array::stream_with_indent(std::ostream & os, size_t local_indent) const {
        os << '[';
        for (const Json & item: * this) {
            os << std::endl;
            for (int i {0}; i < local_indent; ++i)
                os << ' ';
            switch (item.data.index()) {
                case DataType::JSON_OBJECT_TYPE:
                    std::get<DataType::JSON_OBJECT_TYPE>(item.data)->stream_with_indent(
                            os, local_indent + indent_length);
                    break;
                case DataType::ARRAY_TYPE:
                    std::get<DataType::ARRAY_TYPE>(item.data)->stream_with_indent(
                            os, local_indent + indent_length);
                    break;
                case DataType::STRING_TYPE:
                    os << item.serialize();
                    break;
                default:
                    os << item;
            }
            os << (item == * std::prev(end()) ? "" : ",");
        }
        os << '\n' << std::setw(local_indent - indent_length + 1) << ']';
        return os;
    }

    #pragma endregion

}

