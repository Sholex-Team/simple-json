#include "serializer.h"

using namespace simple_json;
using namespace ::types;
using namespace ::indent;
using namespace ::exceptions;
using namespace ::serializer;

#pragma region Serializer Functions

std::string serializer::dumps(const Json & json, size_t local_indent) {
    std::stringstream stream;
    size_t old_indent = switch_indent(local_indent);
    stream << json;
    indent_length = old_indent;
    return std::move(stream.str());
}

void serializer::dump(Json & json, const std::string & file_name, size_t local_indent) {
    std::ofstream file_stream;
    try {
        file_stream.open(file_name);
        if (!file_stream) {
            if (file_stream.is_open()) {
                file_stream.close();
            }
            throw WritingToFileException();
        }
        size_t old_indent = switch_indent(local_indent);
        file_stream << json;
        indent_length = old_indent;
        file_stream.close();
    } catch (std::exception & e) {
        if (file_stream.is_open()) {
            file_stream.close();
        }
    }
}

#pragma endregion
