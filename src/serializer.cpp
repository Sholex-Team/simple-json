#include "serializer.h"

namespace simple_json::serializer {
    #pragma region Serializer Functions

    std::string dumps(const types::Json & json, const size_t local_indent) {
        std::stringstream stream;
        serializer(stream, json, local_indent);
        return stream.str();
    }

    void dump(const types::Json & json, const std::string & file_path, const size_t local_indent) {
        Dump {file_path, local_indent}.dump(json);
    }

    void dump(const types::Json & json, std::ofstream & file_stream, const size_t local_indent) {
        if (!file_stream.is_open()) {
            throw exceptions::WritingToFileException {};
        }
        serializer(file_stream, json, local_indent);
    }

    #pragma endregion


    namespace {
    #pragma region Constructors

        Dump::Dump(const std::string & file_path, const size_t local_indent) :
        file_stream {file_path}, local_indent {local_indent} {
            if (!file_stream) {
                if (file_stream.is_open()) {
                    file_stream.close();
                }
                throw exceptions::WritingToFileException {};
            }
        }

    #pragma endregion

    #pragma region Public Methods

    void Dump::dump(const types::Json & json) {
            serializer(file_stream, json, local_indent);
    }

    #pragma endregion

    #pragma region Destructor

    Dump::~Dump() {
        if (file_stream.is_open()) {
            file_stream.close();
        }
    }

    #pragma endregion

    void serializer(std::ostream & os, const types::Json & json, const size_t local_indent) {
            size_t old_indent = indent::switch_indent(local_indent);
            if (json.type() == types::DataType::string_type) {
                os << json.serialize();
            } else {
                os << json;
            }
            indent::indent_length = old_indent;
        }
    }
}
