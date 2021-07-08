#ifndef SIMPLE_JSON_BASE_ITERATOR_H
#define SIMPLE_JSON_BASE_ITERATOR_H

#include "json_key.h"
#include "enum_types.h"
#include "exceptions/iterator_exceptions.h"
#include "exceptions/invalid_operator.h"

namespace simple_json::iterators {
    /*!
     * @brief Base Json Iterator class.
     *
     * JsonIterator class is the base class that all other iterators inside this project are derived from.
     */
    class JsonIterator {
    protected:
        types::IteratorTypes used_type;
        virtual void increment_iterator() = 0;
        virtual void decrement_iterator() = 0;
        void check_json_object() const;
        void check_array_type() const;
    public:
        // Constructors
        /*!
         * @brief Json Iterator constructor.
         *
         * This constructor takes an argument which represents the iterator type.
         * @param used_type Type of the iterator which is about to be created.
         */
        explicit JsonIterator(types::IteratorTypes used_type);

        /*!
         * @brief Json Iterator copy constructor.
         *
         * This copy constructor is a default copy constructor getting created by compiler.
         */
        JsonIterator(JsonIterator &) = default;

        // Public Methods
        /*!
         * @brief Key method which returns iterator key.
         *
         * This public method will give you the key of a Json object inside a map which the current iterator is pointing
         * to. it can not be used without getting overridden in derived iterator classes.
         * @return A constant reference to a JsonKey object.
         */
        virtual const simple_json::types::JsonKey & key() const = 0;

        /*!
         * @brief Checks the type of the iterator.
         *
         * This public method checks the type of the iterator.
         * @throw exceptions::InvalidIterator Throws this exception if the type is not as same as the given type.
         * @param target_type The type which is about to get checked against current iterator type.
         */
        void check_type(types::IteratorTypes target_type) const;

        // Destructor
        /*!
         * @brief JsonIterator base destructor.
         *
         * This destructor is the base destructor of JsonIterator and will be created by the compiler.
         */
        virtual ~JsonIterator() noexcept = default;
    };
}

/*! @namespace simple_json::iterators
 * @brief A namespace dedicated to iterators.
 *
 * This namespace contains all of iterators and other related parts used inside the project.
 */

/*! @example iterator.cpp
 * @brief Iterators usage example.
 */

#endif //SIMPLE_JSON_BASE_ITERATOR_H
