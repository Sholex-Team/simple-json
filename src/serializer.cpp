#include "serializer.h"

using namespace simple_json;
using namespace ::types;
using namespace ::indent;
using namespace ::exceptions;

#pragma region Serializer Functions

std::string serializer::dumps(const Json & json, size_t local_indent) {
    std::stringstream stream;
    size_t old_indent = switch_indent(local_indent);
    stream << json;
    indent_length = old_indent;
    return std::move(stream.str());
}

void serializer::dump(const Json & json, const std::string & file_name, size_t local_indent) {
    std::ofstream output_file {file_name};
    if (!output_file) {
        if (output_file.is_open()) {
            output_file.close();
        }
        throw WritingToFileException();
    }
    size_t old_indent = switch_indent(local_indent);
    output_file << json;
    indent_length = old_indent;
    output_file.close();
}

#pragma endregion
