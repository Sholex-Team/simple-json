#ifndef SIMPLE_JSON_ITERATOR_EXCEPTIONS_H
#define SIMPLE_JSON_ITERATOR_EXCEPTIONS_H

#include "base_exceptions.h"
#include "../enum_types.h"

/*!
 * @brief A namespace dedicated to iterator related exceptions.
 *
 * This namespace contains exceptions which are related to iterator types used in this project.
 */
namespace simple_json::iterators::exceptions {
    /*!
     * @brief Invalid Dereference exception.
     *
     * This exception throws when when a dereference (*) is happening on a JsonObject iterator.
     */
    class InvalidDereference : public base_exceptions::JsonException {
    public:
        [[nodiscard]] const char * what() const noexcept override;
    };

    /*!
     * @brief Invalid Iteration exception.
     *
     * This exception throws when you try to iterate on a non-iterable Json type.
     */
    class InvalidIteration : public base_exceptions::JsonException {
    private:
        types::DataType used_type;
    public:
        /*!
         * @brief InvalidIteration constructor.
         *
         * This constructor takes an optional argument which is the invalid Json type that iteration happened on.
         * @param used_type Json type used.
         */
        explicit InvalidIteration(types::DataType used_type = types::DataType::UNKNOWN);
        [[nodiscard]] const char * what() const noexcept override;
    };

    /*!
     * @brief Invalid Type exception.
     *
     * This exception throws when you try to access key, value or items method on a non-JsonObject type.
     */
    class InvalidType : public base_exceptions::JsonException {
    public:
        [[nodiscard]] const char * what() const noexcept override;
    };

    /*!
     * @brief Invalid Iterator exception.
     *
     * This exception throws when you try to perform an operation on an invalid iterator.
     */
    class InvalidIterator : public base_exceptions::JsonException {
    private:
        types::IteratorType used_type;
    public:
        /*!
         * @brief InvalidIterator constructor.
         *
         * This constructor takes an optional argument which represents the invalid iterator type that the operation is
         * being performed on.
         * @param used_type Invalid iterator type.
         */
        explicit InvalidIterator(types::IteratorType used_type);
        [[nodiscard]] const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_ITERATOR_EXCEPTIONS_H
