/**
 * @file Sorter.h
 * @brief Declaration of the abstract Sorter class template.
 */
#pragma once
#include <cstddef>
#include <vector>
#include <functional>

/**
 * @class Sorter
 * @brief Abstract base class for sorting algorithms.
 *
 * Provides a common interface for sorting a std::vector or a plain array.
 * A concrete algorithm only has to implement sortRange().
 *
 * @tparam T Element type.
 * @tparam Compare Comparator type. Must return true if the first argument
 * should go before the second one. Defaults to std::less<T>.
 */
template <typename T,typename Compare=std::less<T>>
class Sorter{
protected:
    Compare comp;///<Comparator used to order elements.

    /**
     * @brief Sorts the range [begin, end). Implemented by derived classes.
     * @param begin Pointer to the first element.
     * @param end Pointer one past the last element.
     */
    virtual void sortRange(T* begin, T* end) = 0;

public:
    /**
     * @brief Constructs a sorter with the given comparator.
     * @param comparator Comparator object.
     */
    explicit Sorter(Compare comparator=Compare()): comp(comparator){}

    /** @brief Virtual destructor. */
    virtual ~Sorter() = default;

    /**
     * @brief Sorts a std::vector in place.
     * @param vec Vector to sort. Vectors with fewer than two elements are left unchanged.
     */
    void sort(std::vector<T>& vec) {
        if (vec.size() <= 1) return;
        sortRange(vec.data(), vec.data() + vec.size());
    }

    /**
     * @brief Sorts a plain array in place.
     * @param arr Pointer to the first element. A null pointer is ignored.
     * @param size Number of elements. Sizes below two leave the array unchanged.
     */
    void sort(T* arr, std::size_t size) {
        if (!arr || size <= 1) return;
        sortRange(arr, arr + size);
    }
};