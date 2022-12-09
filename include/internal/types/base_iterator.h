#ifndef SIMPLE_JSON_BASE_ITERATOR_H
#define SIMPLE_JSON_BASE_ITERATOR_H

#include <utility>
#include <variant>
#include "json_key.h"
#include "enum_types.h"
#include "exceptions/iterator_exceptions.h"
#include "exceptions/invalid_operator.h"

namespace simple_json::types {
    class Json;
}

namespace simple_json::iterators {
    using namespace types;

    /*!
     * @brief Json base iterator class
     *
     * JsonIterator class is the base class that all other iterators inside this project are derived from.
     */
    class BaseJsonIterator {
    protected:
        // Protected Methods
        virtual void increment_iterator() = 0;
        virtual void decrement_iterator() = 0;
    public:
        // Friends
        friend class types::Json;
    };

    /*!
     * @brief Base Json Iterator class.
     * @tparam ArrayIterator Inner Array iterator type
     * @tparam JsonObjectIterator Inner JsonObject iterator type
     * @tparam ReturnType Inner value type
     */
    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    class JsonIterator : public BaseJsonIterator {
    protected:
        // Protected Properties
        using variant_type = std::variant<std::monostate, ArrayIterator *, JsonObjectIterator *>;
        variant_type data;

        // Protected Methods
        void increment_iterator() override;
        void decrement_iterator() override;
        void clean_memory() noexcept;
    public:
        // Constructors
        /*!
         * @brief JsonIterator Array iterator types constructor
         *
         * @param array_iterator const reference to Array iterator which is going to be used as inner iterator
         */
        [[nodiscard]] explicit JsonIterator(const ArrayIterator & array_iterator);

        /*!
         * @brief JsonIterator JsonObject iterator types constructor
         *
         * @param json_object_iterator const reference to JsonObject iterator which is going to be used as inner iterator
         */
        [[nodiscard]] explicit JsonIterator(const JsonObjectIterator & json_object_iterator);

        /*!
         * @brief JsonIterator copy constructor
         *
         * This constructor Deep copies inner iterator and used_type.
         */
        [[nodiscard]] JsonIterator(const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &json_iterator);


        /*!
         * @brief JsonIterator move constructor
         *
         * This constructor moves the inner iterator and used_type.
         */
        [[nodiscard]] JsonIterator(JsonIterator<ArrayIterator,
                                   JsonObjectIterator, ReturnType> && json_iterator) noexcept;

        // Public Methods
        template<IteratorType T>
        [[nodiscard]] auto check_type() const -> decltype(std::get<T>(const_cast<variant_type &>(data)));
        /*!
         * @brief Key method which returns iterator key.
         *
         * This public method will give you the key of a Json object inside a map which the current iterator is pointing
         * to. it can not be used without getting overridden in derived iterator classes.
         * @return A constant reference to a JsonKey object.
         */
        [[nodiscard]] const JsonKey &key() const;

        /*!
         * @brief Returns the value of object that the iterator is pointing to.
         *
         * This method returns a reference to the value(second item) of the std::pair that the
         * iterator is pointing to within a JsonObject.
         * @return A reference to a Json object.
         */
        [[nodiscard]] ReturnType &value() const;


        // Operator Overloading
        /*!
         * @brief JsonIterator dereference operator overload.
         * @throw iterators::exceptions::InvalidDereference Throws when the inner iterator is not a Array iterator.
         * @return Json object which the iterator is pointing to.
         */
        [[nodiscard]] ReturnType & operator*() const;

        /*!
         * @brief iterator post-increment operator overload.
         *
         * This operator copies the iterator object and increments the original iterator by one position.
         * @return A const copy of iterator object before incrementing.
         */
        const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> operator++(int);

        /*!
         * @brief iterator pre-increment operator overload.
         *
         * This operator increments the iterator by one position.
         * @return A reference to Incremented operator.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &operator++();

        /*!
         * @brief iterator post-decrement operator overload.
         *
         * This operator copies the iterator object and decrements the original iterator by one position.
         * @return A const copy of iterator object before decrementing.
         */
        const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> operator--(int);

        /*!
         * @brief iterator pre-decrement operator overload.
         *
         * This operator decrements the iterator by one position.
         * @return A reference to decremented operator.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &operator--();

        /*!
         * @brief iterator addition operator overload.
         *
         * This operator copies the iterator object and increments the copy by specified positions.
         * @param i Positions that the iterator is going to get incremented by.
         * @return Incremented iterator object.
         */
        [[nodiscard]] JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> operator+(long i) const;

        /*!
         * @brief iterator subtraction operator overload.
         *
         * This operator copies the iterator object and decrements the copy by given positions.
         * @param i Positions that the iterator is going to get decremented by.
         * @return Decremented iterator object.
         */
        [[nodiscard]] JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> operator-(long i) const;

        /*!
         * @brief iterator addition assignment operator overload.
         *
         * This operator increments the iterator by given positions.
         * @param i Positions that the iterator is going to get incremented by.
         * @return Incremented iterator.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & operator+=(long i);

        /*!
         * @brief iteration subtraction assignment operator overload.
         *
         * This operator decrements the iterator by given positions.
         * @param i Positions that the iterator it going to get decremented by.
         * @return Decremented iterator.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & operator-=(long i);

        /*!
         * @brief Not equal to operator overload.
         *
         * This operator checks if iterator is not equal to given operator.
         * @param r_iterator The iterator object which is going to get compared.
         * @return Boolean representing the checking result.
         */
        [[nodiscard]] bool operator!=(const JsonIterator<ArrayIterator,JsonObjectIterator,
                ReturnType> &r_iterator) const;

        /*!
         * @brief equality operator overload.
         *
         * This operator checks if iterator is equal to a given iterator.
         * @param r_iterator The iterator object which is going to get compared.
         * @return Boolean representing the checking result.
         */
        [[nodiscard]] bool operator==(const JsonIterator<ArrayIterator,
                JsonObjectIterator, ReturnType> &r_iterator) const;

        /*!
         * @brief JsonIterator copy assignment operator
         * @param r_iterator JsonIterator which the current object to going to be assigned to
         * @return A reference to the JsonIterator
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &operator=(
                const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &r_iterator);

        /*!
         * @brief JsonIterator move assignment operator
         *
         * This operator overload moves the passed JsonIterator into the current JsonIterator object.
         * @param r_iterator JsonIterator which is about to be moved into the current object
         * @return A reference to the JsonIterator
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &operator=(
                JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> && r_iterator) noexcept;

        // Destructors
        ~JsonIterator() noexcept;

        // Friends
        friend class types::Json;
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
