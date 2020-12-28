#include "serializer.h"

namespace simple_json::serializer {
    #pragma region Serializer Functions

    std::string dumps(const types::Json & json, size_t local_indent) {
        std::stringstream stream;
        size_t old_indent = indent::switch_indent(local_indent);
        stream << json;
        indent::indent_length = old_indent;
        return std::move(stream.str());
    }

    void dump(types::Json & json, const std::string & file_name, size_t local_indent) {
        Dump(json, file_name, local_indent);
    }

    namespace {
        Dump::Dump(const types::Json &json, const std::string &file_name, size_t local_indent) :
                file_stream {file_name} {
            if (!file_stream) {
                if (file_stream.is_open()) {
                    file_stream.close();
                }
                throw exceptions::WritingToFileException();
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

