#ifndef SIMPLE_JSON_BASE_ITERATOR_H
#define SIMPLE_JSON_BASE_ITERATOR_H

#include "json_key.h"
#include "enum_types.h"
#include "exceptions/iterator_exceptions.h"
#include "exceptions/invalid_operator.h"

namespace simple_json::iterators {
    class JsonIterator {
    protected:
        types::IteratorTypes used_type;
        virtual void add_to_iterator() = 0;
        void check_json_object() const;
        void check_array_type() const;
    public:
        // Constructors
        explicit JsonIterator(types::IteratorTypes used_type);
        JsonIterator(JsonIterator &) = default;

        // Public Methods
        virtual const simple_json::types::JsonKey & key() const = 0;
        void check_type(types::IteratorTypes target_type) const;

        // Destructor
        virtual ~JsonIterator() noexcept = default;
    };
}

#endif //SIMPLE_JSON_BASE_ITERATOR_H
