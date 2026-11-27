/**
 * @file GraphIterators.ipp
 * @brief Implementation of the Graph::Iter iterator template.
 */
#pragma once
#include "Graph.hpp"

/**
 * @class Graph::Iter
 * @brief Bidirectional graph iterator.
 *
 * A single template describes all 16 iterators: over vertices, edges, incident
 * edges and adjacent vertices, in forward and reverse variants, constant and
 * non-constant. The vertex iterator returns a vertex value, the edge and
 * incident edge iterators return a std::pair of endpoint values, and the
 * adjacent vertex iterator returns the value of the neighbouring vertex. A
 * reverse iterator stores a position one element past the current one.
 *
 * @tparam K Iterator kind (IterKind).
 * @tparam C true for a constant iterator.
 * @tparam R true for a reverse iterator.
 */
template <typename T>
template <IterKind K, bool C, bool R>
class Graph<T>::Iter {
  /// Whether the iterator returns a single value (a vertex) rather than a pair.
  static constexpr bool returnsSingleValue =
      (K == IterKind::Vertex) || (K == IterKind::Adjacent);

  /// Container being iterated over.
  using Container = std::conditional_t<K == IterKind::Vertex, VerticesContainer,
                                       EdgesContainer>;

  /// Iterator type of the underlying container.
  using ContainerIterator =
      std::conditional_t<C, typename Container::const_iterator,
                         typename Container::iterator>;

  /// Pointer type to the source vertex (for incident and adjacent iterators).
  using SourceVertexPtr =
      std::conditional_t<C, const VertexNode *, VertexNode *>;

public:
  using iterator_category =
      std::bidirectional_iterator_tag;    ///< Iterator category.
  using difference_type = std::ptrdiff_t; ///< Iterator difference type.
  using value_type = std::conditional_t<returnsSingleValue, T,
                                        std::pair<T, T>>; ///< Value type.

  /// Whether the iterator allows modifying the value (only non-const vertex
  /// iterators).
  static constexpr bool isMutable = (K == IterKind::Vertex) && !C;

  using reference = std::conditional_t<isMutable, T &,
                                       const value_type &>; ///< Reference type.
  using pointer = std::remove_reference_t<reference> *;     ///< Pointer type.

  /** @brief Default constructor. */
  Iter() = default;

  /**
   * @brief Constructs an iterator from an iterator of the underlying container.
   * @param position Position in the container.
   * @param sourceVertex Vertex the iteration is relative to (for Incident and
   * Adjacent kinds).
   */
  Iter(ContainerIterator position, SourceVertexPtr sourceVertex = nullptr)
      : position(position), sourceVertex(sourceVertex) {}

  /**
   * @brief Converts a non-constant iterator to a constant one.
   * @tparam SourceC Constness of the source iterator.
   * @param other Non-constant iterator.
   */
  template <bool SourceC, typename = std::enable_if_t<C && !SourceC>>
  Iter(const Iter<K, SourceC, R> &other)
      : position(other.position), sourceVertex(other.sourceVertex) {}

  /**
   * @brief Dereferences the iterator.
   * @return Vertex value, or a pair of endpoint values of an edge.
   */
  reference operator*() const {
    auto it = R ? std::prev(position) : position;
    if constexpr (K == IterKind::Vertex) {
      return (*it)->value;
    } else if constexpr (K == IterKind::Edge) {
      auto firstEnd = (*it)->u.lock()->value;
      auto secondEnd = (*it)->v.lock()->value;
      cached = (firstEnd < secondEnd) ? std::make_pair(firstEnd, secondEnd)
                                      : std::make_pair(secondEnd, firstEnd);
      return cached;
    } else if constexpr (K == IterKind::Incident) {
      cached = std::make_pair(sourceVertex->value,
                              otherEnd(**it, sourceVertex)->value);
      return cached;
    } else {
      cached = otherEnd(**it, sourceVertex)->value;
      return cached;
    }
  }

  /**
   * @brief Member access to the current value.
   * @return Pointer to the current value.
   */
  pointer operator->() const { return &**this; }

  /**
   * @brief Prefix increment.
   * @return Reference to this iterator.
   */
  Iter &operator++() {
    R ? --position : ++position;
    return *this;
  }

  /**
   * @brief Postfix increment.
   * @return Copy of the iterator before incrementing.
   */
  Iter operator++(int) {
    auto old = *this;
    ++*this;
    return old;
  }

  /**
   * @brief Prefix decrement.
   * @return Reference to this iterator.
   */
  Iter &operator--() {
    R ? ++position : --position;
    return *this;
  }

  /**
   * @brief Postfix decrement.
   * @return Copy of the iterator before decrementing.
   */
  Iter operator--(int) {
    auto old = *this;
    --*this;
    return old;
  }

  /**
   * @brief Equality comparison.
   * @param other Iterator to compare with.
   * @return true if both the positions and the source vertices are equal.
   */
  bool operator==(const Iter &other) const {
    return position == other.position && sourceVertex == other.sourceVertex;
  }

  /**
   * @brief Inequality comparison.
   * @param other Iterator to compare with.
   * @return true if the iterators differ.
   */
  bool operator!=(const Iter &other) const { return !(*this == other); }

private:
  ContainerIterator
      position{}; ///< Current position in the underlying container.
  SourceVertexPtr sourceVertex =
      nullptr; ///< Source vertex for incident and adjacent iterators.

  mutable std::conditional_t<K == IterKind::Vertex, char, value_type>
      cached{}; ///< Cached value that the returned reference points to.

  friend class Graph<T>;
  template <IterKind K2, bool C2, bool R2> friend class Iter;
};