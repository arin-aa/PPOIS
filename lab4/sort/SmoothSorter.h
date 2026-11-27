/**
 * @file SmoothSorter.h
 * @brief Declaration of the SmoothSorter class template (Dijkstra's
 * smoothsort).
 */
#pragma once
#include "Sorter.h"
#include <utility>

/**
 * @class SmoothSorter
 * @brief Smoothsort by Dijkstra.
 *
 * Worst case O(n log n), O(n) on nearly sorted data, O(1) additional memory
 * (not counting the forest of O(log n) trees).
 *
 * The array is treated as a forest of Leonardo heap trees whose orders decrease
 * from left to right. A tree of order k occupies L[k] elements:
 * @code
 * [ left subtree of order k-1 ][ right subtree of order k-2 ][ root ]
 * @endcode
 * Forest roots are in ascending order, so the last root is the maximum.
 *
 * Leonardo numbers: L[0] = L[1] = 1, L[k] = L[k-1] + L[k-2] + 1.
 *
 * @tparam T Element type.
 * @tparam Compare Comparator type. Defaults to std::less<T>.
 */
template <typename T, typename Compare = std::less<T>>
class SmoothSorter : public Sorter<T, Compare> {
  using Sorter<T, Compare>::comp;

  /**
   * @struct LeonardoTree
   * @brief Describes one tree of the forest.
   */
  struct LeonardoTree {
    std::size_t order;     ///< Tree order k.
    std::size_t rootIndex; ///< Index of the tree root in the array.
  };
  using Forest = std::vector<LeonardoTree>; ///< Forest of Leonardo trees,
                                            ///< ordered left to right.

  std::vector<std::size_t>
      leo; ///< Leonardo numbers not exceeding the array size.

private:
  /**
   * @brief Fills the table of Leonardo numbers.
   * @param size Array size; numbers larger than it are not generated.
   */
  void fillLeonardo(std::size_t size) {
    leo.assign({1, 1});
    while (leo[leo.size() - 1] + leo[leo.size() - 2] + 1 <= size) {
      leo.push_back(leo[leo.size() - 1] + leo[leo.size() - 2] + 1);
    }
  }

  /**
   * @brief Returns the index of the right child (order k-2).
   * @param root Index of the tree root.
   * @return Index of the right child, which stands right before the root.
   */
  std::size_t rightChild(std::size_t root) const { return root - 1; }

  /**
   * @brief Returns the index of the left child (order k-1).
   * @param root Index of the tree root.
   * @param order Order of the tree (at least 2).
   * @return Index of the left child, which stands before the right subtree.
   */
  std::size_t leftChild(std::size_t root, std::size_t order) const {
    return root - 1 - leo[order - 2];
  }

  /**
   * @brief Sifts a root down inside a single tree.
   * @param arr Array being sorted.
   * @param root Index of the root to sift.
   * @param order Order of the tree.
   */
  void sift(T *arr, std::size_t root, std::size_t order) {
    using std::swap;
    while (order >= 2) {
      std::size_t right = rightChild(root);
      std::size_t left = leftChild(root, order);
      std::size_t child, childOrder;
      if (comp(arr[right], arr[left])) {
        child = left;
        childOrder = order - 1;
      } else {
        child = right;
        childOrder = order - 2;
      }
      if (!comp(arr[root], arr[child]))
        break;
      swap(arr[root], arr[child]);
      root = child;
      order = childOrder;
    }
  }

  /**
   * @brief Restores the order for the tree forest[idx].
   *
   * First moves its root to the left along the forest roots (while the previous
   * root is greater than the whole tree), then sifts it down.
   *
   * @param arr Array being sorted.
   * @param forest Current forest.
   * @param idx Index of the tree in the forest.
   */
  void trinkle(T *arr, const Forest &forest, std::size_t idx) {
    using std::swap;
    std::size_t root = forest[idx].rootIndex;
    std::size_t order = forest[idx].order;
    while (idx > 0) {
      std::size_t prev = forest[idx - 1].rootIndex;
      if (!comp(arr[root], arr[prev]))
        break;
      if (order >= 2) {
        if (comp(arr[prev], arr[rightChild(root)]) ||
            comp(arr[prev], arr[leftChild(root, order)]))
          break;
      }
      swap(arr[prev], arr[root]);
      --idx;
      root = prev;
      order = forest[idx].order;
    }
    sift(arr, root, order);
  }

  /**
   * @brief Adds the element arr[i] to the forest.
   * @param arr Array being sorted.
   * @param i Index of the element to add.
   * @param forest Forest to extend.
   */
  void addElement(T *arr, std::size_t i, Forest &forest) {
    std::size_t n = forest.size();
    if (n >= 2 && forest[n - 2].order == forest[n - 1].order + 1) {
      std::size_t order = forest[n - 2].order + 1;
      forest.pop_back();
      forest.back() = {order, i};
    } else if (n >= 1 && forest[n - 1].order == 1) {
      forest.push_back({0, i});
    } else {
      forest.push_back({1, i});
    }
    trinkle(arr, forest, forest.size() - 1);
  }

  /**
   * @brief Removes the maximum (the root of the last tree, located at position
   * i).
   * @param arr Array being sorted.
   * @param i Index of the maximum element.
   * @param forest Forest to shrink.
   */
  void popMax(T *arr, std::size_t i, Forest &forest) {
    LeonardoTree last = forest.back();
    forest.pop_back();
    if (last.order >= 2) {
      forest.push_back({last.order - 1, leftChild(i, last.order)});
      trinkle(arr, forest, forest.size() - 1);
      forest.push_back({last.order - 2, rightChild(i)});
      trinkle(arr, forest, forest.size() - 1);
    }
  }

  /**
   * @brief Sorts the range [begin, end) with smoothsort.
   * @param begin Pointer to the first element.
   * @param end Pointer one past the last element.
   */
  void sortRange(T *begin, T *end) override {
    std::size_t n = static_cast<std::size_t>(end - begin);
    if (n <= 1) {
      return;
    }
    fillLeonardo(n);

    Forest forest;
    for (std::size_t i = 0; i < n; ++i) {
      addElement(begin, i, forest);
    }
    for (std::size_t i = n; i-- > 0;) {
      popMax(begin, i, forest);
    }
  }

public:
  /**
   * @brief Constructs a smoothsort sorter.
   * @param comparator Comparator object.
   */
  explicit SmoothSorter(Compare comparator = Compare())
      : Sorter<T, Compare>(comparator) {}
};