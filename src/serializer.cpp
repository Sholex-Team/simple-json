#include "serializer.h"

namespace simple_json::serializer {
    #pragma region Serializer Functions

    std::string dumps(const types::Json & json, size_t local_indent) {
        std::stringstream stream;
        size_t old_indent = indent::switch_indent(local_indent);
        if (json.type() == types::DataType::string_type) {
            stream << json.serialize();
        } else {
            stream << json;
        }
        indent::indent_length = old_indent;
        return stream.str();
    }

    void dump(types::Json & json, const std::string & file_name, size_t local_indent) {
        Dump(json, file_name, local_indent);
    }

    void dump(types::Json & json, std::ofstream & file_stream, size_t local_indent) {
        if (!file_stream) {
            throw exceptions::WritingToFileException {};
        }
        if (!file_stream.is_open()) {
            throw exceptions::WritingToFileException {};
        }
        size_t old_indent = indent::switch_indent(local_indent);
        if (json.type() == types::DataType::string_type) {
            file_stream << json.serialize();
        } else {
            file_stream << json;
        }
        indent::indent_length = old_indent;
    }

    namespace {
        Dump::Dump(const types::Json &json, const std::string &file_name, size_t local_indent) :
                file_stream {file_name} {
            // TODO: Move constructor instructions to a public method.
            if (!file_stream) {
                if (file_stream.is_open()) {
                    file_stream.close();
                }
                throw exceptions::WritingToFileException {};
            }
            size_t old_indent = indent::switch_indent(local_indent);
            file_stream << json;
            indent::indent_length = old_indent;
            file_stream.close();
        }

        Dump::~Dump() {
            if (file_stream.is_open()) {
                file_stream.close();
            }
        }
    }

    #pragma endregion
}

