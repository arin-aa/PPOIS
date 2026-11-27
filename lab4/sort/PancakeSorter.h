/**
 * @file PancakeSorter.h
 * @brief Declaration of the PancakeSorter class template (simple pancake sort).
 */
#pragma once
#include "Sorter.h"
#include <algorithm>
#include <functional>
#include <utility>

/**
 * @class PancakeSorter
 * @brief Simple pancake sort.
 *
 * For each shrinking prefix the maximum is found, flipped to the front
 * (reversing the prefix that ends at the maximum) and then flipped to the end
 * of the current prefix. O(n^2) comparisons, O(1) additional memory.
 * The sort is not stable.
 *
 * @tparam T Element type.
 * @tparam Compare Comparator type. Defaults to std::less<T>.
 */
template <typename T, typename Compare = std::less<T>>
class PancakeSorter : public Sorter<T, Compare> {
private:
  using Sorter<T, Compare>::comp;

  /**
   * @brief Sorts the range [begin, end) with pancake sort.
   * @param begin Pointer to the first element.
   * @param end Pointer one past the last element.
   */
  void sortRange(T *begin, T *end) override {
    std::size_t n = end - begin;
    for (std::size_t currSize = n; currSize > 1; currSize--) {
      std::size_t maxIndex = 0;
      for (std::size_t i = 1; i < currSize; i++) {
        if (comp(begin[maxIndex], begin[i])) {
          maxIndex = i;
        }
      }
      if (maxIndex == currSize - 1) {
        continue;
      }
      std::size_t left = 0;
      std::size_t right = maxIndex;
      if (maxIndex != 0) {
        while (left < right) {
          std::swap(begin[left], begin[right]);
          ++left;
          --right;
        }
      }
      std::size_t lef = 0;
      std::size_t righ = currSize - 1;
      while (lef < righ) {
        std::swap(begin[lef], begin[righ]);
        ++lef;
        --righ;
      }
    }
  }

public:
  /**
   * @brief Constructs a pancake sorter.
   * @param comparator Comparator object.
   */
  explicit PancakeSorter(Compare comparator = Compare())
      : Sorter<T, Compare>(comparator) {}
};