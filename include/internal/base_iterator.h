#ifndef SIMPLE_JSON_BASE_ITERATOR_H
#define SIMPLE_JSON_BASE_ITERATOR_H

#include "json_key.h"
#include "enum_types.h"
#include "iterator_exceptions.h"

namespace simple_json::iterators {
    class JsonIterator {
    protected:
        types::IteratorTypes used_type;
        virtual void add_to_iterator() = 0;
        void check_json_object() const;
    public:
        // Constructors
        explicit JsonIterator(types::IteratorTypes);
        JsonIterator(JsonIterator &) = default;

        // Public Methods
        virtual const simple_json::types::JsonKey & key() const = 0;

        // Destructor
        virtual ~JsonIterator() noexcept = default;
    };
}

#endif //SIMPLE_JSON_BASE_ITERATOR_H
