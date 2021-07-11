#ifndef SIMPLE_JSON_BASE_ITERATOR_H
#define SIMPLE_JSON_BASE_ITERATOR_H

#include "json_key.h"
#include "enum_types.h"
#include "exceptions/iterator_exceptions.h"
#include "exceptions/invalid_operator.h"
#include <utility>

namespace simple_json::iterators {
    using namespace types;
    class Json;

    /*!
     * @brief Json base iterator class
     *
     * JsonIterator class is the base class that all other iterators inside this project are derived from.
     */
    class BaseJsonIterator {
    protected:
        // Protected Properties
        IteratorTypes used_type;

        // Protected Methods
        void check_json_object() const;
        void check_array_type() const;
    public:
        // Constructors
        /*!
         * @brief BaseJsonIterator iterator
         * @param used_type Inner iterator type
         */
        explicit BaseJsonIterator(IteratorTypes used_type);

        /*!
         * @brief BaseJsonIterator default copy constructor
         * @param base_json_iterator BaseJsonIterator which is about to get copied
         */
        BaseJsonIterator(const BaseJsonIterator & base_json_iterator) = default;

        /*!
         * @brief Checks the type of the iterator.
         *
         * This public method checks the type of the iterator.
         * @throw exceptions::InvalidIterator Throws this exception if the type is not as same as the given type.
         * @param target_type The type which is about to get checked against current iterator type.
         */
        void check_type(IteratorTypes target_type) const;
    };

    /*!
     * @brief Base Json Iterator class.
     * @tparam ArrayIterator Inner Array iterator type
     * @tparam JsonObjectIterator Inner JsonObject iterator type
     */
    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    class JsonIterator : public BaseJsonIterator {
    protected:
        union {
            ArrayIterator * array_iterator;
            JsonObjectIterator * json_object_iterator;
        };
    private:
        // Private Methods
        void increment_iterator() {
            if (used_type == IteratorTypes::array_iterator_type)
                ++ * array_iterator;
            else
                ++ * json_object_iterator;
        }

        void decrement_iterator() {
            if (used_type == IteratorTypes::array_iterator_type)
                -- * array_iterator;
            else
                -- * json_object_iterator;
        }

        void clean_memory() {
            if (used_type == IteratorTypes::array_iterator_type)
                delete array_iterator;
            else
                delete json_object_iterator;
        }
    public:
        // Constructors
        /*!
         * @brief JsonIterator Array iterator types constructor
         *
         * @param a const reference to Array iterator which is going to be used as inner iterator
         */
        explicit JsonIterator(const ArrayIterator & array_iterator) :
        BaseJsonIterator {IteratorTypes::array_iterator_type},
        array_iterator {new ArrayIterator {array_iterator}} {}

        /*!
         * @brief JsonIterator JsonObject iterator types constructor
         *
         * @param a const reference to JsonObject iterator which is going to be used as inner iterator
         */
        explicit JsonIterator(const JsonObjectIterator & json_object_iterator) :
        BaseJsonIterator {IteratorTypes::json_object_iterator_type},
        json_object_iterator {new JsonObjectIterator {json_object_iterator}} {}

        /*!
         * @brief JsonIterator copy constructor
         *
         * This constructor Deep copies inner iterator and used_type.
         */
        JsonIterator(const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & json_iterator) :
        BaseJsonIterator {json_iterator.used_type} {
            if (used_type == IteratorTypes::array_iterator_type) {
                array_iterator = new ArrayIterator {* json_iterator.array_iterator};
                return;
            }
            json_object_iterator = new JsonObjectIterator {* json_iterator.json_object_iterator};
        }


        /*!
         * @brief JsonIterator move constructor
         *
         * This constructor moves the inner iterator and used_type.
         */
        JsonIterator(JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> && json_iterator) noexcept :
        BaseJsonIterator {json_iterator.used_type} {
            if (used_type == IteratorTypes::array_iterator_type) {
                array_iterator = json_iterator.array_iterator;
                json_iterator.array_iterator = nullptr;
                return;
            }
            json_object_iterator = json_iterator.json_object_iterator;
            json_iterator.json_object_iterator = nullptr;
        }

        // Public Methods
        /*!
         * @brief Key method which returns iterator key.
         *
         * This public method will give you the key of a Json object inside a map which the current iterator is pointing
         * to. it can not be used without getting overridden in derived iterator classes.
         * @return A constant reference to a JsonKey object.
         */
        const JsonKey & key() const {
            check_json_object();
            return (* json_object_iterator)->first;
        }

        /*!
         * @brief Returns the value of object that the iterator is pointing to.
         *
         * This method returns a reference to the value(second item) of the std::pair that the
         * iterator is pointing to within a JsonObject.
         * @return A reference to a Json object.
         */
        ReturnType & value() const {
            check_json_object();
            return (* json_object_iterator)->second;
        }

        // Operator Overloading
        /*!
         * @brief JsonIterator dereference operator overload.
         * @throw iterators::exceptions::InvalidDereference Throws when the inner iterator is not a Array iterator.
         * @return Json object which the iterator is pointing to.
         */
        ReturnType & operator*() const {
            if (used_type != IteratorTypes::array_iterator_type) {
                throw iterators::exceptions::InvalidDereference {};
            }
            return * * array_iterator;
        }

        /*!
         * @brief iterator post-increment operator overload.
         *
         * This operator copies the iterator object and increments the original iterator by one position.
         * @return A const copy of iterator object before incrementing.
         */
        const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> operator++(int) {
            JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> temp {* this};
            increment_iterator();
            return temp;
        }

        /*!
         * @brief iterator pre-increment operator overload.
         *
         * This operator increments the iterator by one position.
         * @return A reference to Incremented operator.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & operator++() {
            increment_iterator();
            return * this;
        }

        /*!
         * @brief iterator post-decrement operator overload.
         *
         * This operator copies the iterator object and decrements the original iterator by one position.
         * @return A const copy of iterator object before decrementing.
         */
        const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> operator--(int) {
            JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> temp {* this};
            decrement_iterator();
            return temp;
        }

        /*!
         * @brief iterator pre-decrement operator overload.
         *
         * This operator decrements the iterator by one position.
         * @return A reference to decremented operator.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & operator--() {
            decrement_iterator();
            return * this;
        }

        /*!
         * @brief iterator addition operator overload.
         *
         * This operator copies the iterator object and increments the copy by specified positions.
         * @param i Positions that the iterator is going to get incremented by.
         * @return Incremented iterator object.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> operator+(long i) const {
            check_array_type();
            return JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> {* array_iterator + i};
        }

        /*!
         * @brief iterator subtraction operator overload.
         *
         * This operator copies the iterator object and decrements the copy by given positions.
         * @param i Positions that the iterator is going to get decremented by.
         * @return Decremented iterator object.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> operator-(long i) const {
            check_array_type();
            return JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> {* array_iterator - i};
        }

        /*!
         * @brief iterator addition assignment operator overload.
         *
         * This operator increments the iterator by given positions.
         * @param i Positions that the iterator is going to get incremented by.
         * @return Incremented iterator.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & operator+=(long i) {
            check_array_type();
            * array_iterator += i;
            return * this;
        }

        /*!
         * @brief iteration subtraction assignment operator overload.
         *
         * This operator decrements the iterator by given positions.
         * @param i Positions that the iterator it going to get decremented by.
         * @return Decremented iterator.
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & operator-=(long i) {
            check_array_type();
            * array_iterator -= i;
            return * this;
        }

        /*!
         * @brief Not equal to operator overload.
         *
         * This operator checks if iterator is not equal to given operator.
         * @param r_iterator The iterator object which is going to get compared.
         * @return Boolean representing the checking result.
         */
        bool operator!=(const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & r_iterator) const {
            if (used_type == IteratorTypes::array_iterator_type) {
                return * array_iterator != * r_iterator.array_iterator;
            }
            return * json_object_iterator != * r_iterator.json_object_iterator;
        }

        /*!
         * @brief equality operator overload.
         *
         * This operator checks if iterator is equal to a given iterator.
         * @param r_iterator The iterator object which is going to get compared.
         * @return Boolean representing the checking result.
         */
        bool operator==(const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & r_iterator) const {
            if (used_type == IteratorTypes::array_iterator_type) {
                return * array_iterator == * r_iterator.array_iterator;
            }
            return * json_object_iterator == * r_iterator.json_object_iterator;
        }

        /*!
         * @brief JsonIterator copy assignment operator
         * @param r_iterator JsonIterator which the current object to going to be assigned to
         * @return A reference to the JsonIterator
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & operator=(
                const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & r_iterator) {
            clean_memory();
            used_type = r_iterator.used_type;
            if (used_type == IteratorTypes::array_iterator_type)
                array_iterator = new ArrayIterator {* r_iterator.array_iterator};
            else
                json_object_iterator = new JsonObjectIterator {* r_iterator.json_object_iterator};
            return * this;
        }

        /*!
         * @brief JsonIterator move assignment operator
         *
         * This operator overload moves the passed JsonIterator into the current JsonIterator object.
         * @param r_iterator JsonIterator which is about to be moved into the current object
         * @return A reference to the JsonIterator
         */
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & operator=(
                JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> && r_iterator) noexcept {
            clean_memory();
            used_type = r_iterator.used_type;
            if (used_type == IteratorTypes::array_iterator_type) {
                array_iterator = r_iterator.array_iterator;
                r_iterator.array_iterator = nullptr;
            } else {
                json_object_iterator = r_iterator.json_object_iterator;
                r_iterator.json_object_iterator = nullptr;
            }
            return * this;
        }

        // Destructor
        /*!
         * @brief JsonIterator base destructor.
         *
         * This destructor is the base destructor of JsonIterator and will be created by the compiler.
         */
        ~JsonIterator() noexcept {
            clean_memory();
        }
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
