/**
 * @class Graph
 * @brief Undirected graph (modified Wirth structure).
 *
 * Vertices are stored in a list of smart pointers, and each vertex keeps a list
 * of its incident edges. An edge holds weak pointers to its endpoints.
 * Duplicate vertices, parallel edges and loops are forbidden.
 */
#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

/**
 * @enum IterKind
 * @brief Kind of graph iterator.
 */
enum class IterKind {
  Vertex,   ///< Iterates over all vertices.
  Edge,     ///< Iterates over all edges.
  Incident, ///< Iterates over edges incident to a given vertex.
  Adjacent  ///< Iterates over vertices adjacent to a given vertex.
};

/**
 * @class Graph
 * @brief Undirected graph (modified Wirth structure).
 *
 * Vertices are stored in a list of smart pointers, and each vertex keeps a list
 * of its incident edges. An edge holds weak pointers to its endpoints.
 * Duplicate vertices and parallel edges are forbidden, loops are allowed. The
 * class supports adding and removing vertices and edges, checking for their
 * presence, computing vertex and edge degrees, and forward, reverse and
 * constant iterators over vertices, edges, incident edges and adjacent
 * vertices.
 *
 * @tparam T Vertex value type. Must support operator== and operator<.
 */
template <typename T> class Graph {
private:
  struct EdgeNode;

  /**
   * @struct VertexNode
   * @brief Vertex node.
   */
  struct VertexNode {
    T value; ///< Vertex value.
    std::list<std::shared_ptr<EdgeNode>>
        incidentEdges; ///< Edges incident to the vertex.
  };

  /**
   * @struct EdgeNode
   * @brief Edge node.
   */
  struct EdgeNode {
    std::weak_ptr<VertexNode> u; ///< First endpoint of the edge.
    std::weak_ptr<VertexNode> v; ///< Second endpoint of the edge.
  };

  using VertexPtr = std::shared_ptr<VertexNode>; ///< Smart pointer to a vertex.
  using VerticesContainer = std::list<VertexPtr>; ///< Container of vertices.
  using EdgesContainer =
      std::list<std::shared_ptr<EdgeNode>>; ///< Container of edges.
  using IncidentContainer =
      EdgesContainer; ///< Container of edges incident to a vertex.
  using Key =
      std::tuple<size_t, size_t, std::vector<T>,
                 std::vector<std::pair<T, T>>>; ///< Key used to compare graphs.

  VerticesContainer vertices; ///< List of all vertices of the graph.
  EdgesContainer edges;       ///< List of all edges of the graph.

  /**
   * @brief Graph iterator template.
   * @tparam K Iterator kind.
   * @tparam C true for a constant iterator.
   * @tparam R true for a reverse iterator.
   */
  template <IterKind K, bool C, bool R> class Iter;

  /**
   * @brief Finds a vertex by value.
   * @param value Vertex value.
   * @return Pointer to the vertex, or nullptr if there is no such vertex.
   */
  VertexPtr findNode(const T &value) const;

  /**
   * @brief Finds a vertex by value and throws if it is missing.
   * @param value Vertex value.
   * @param msg Exception message.
   * @return Pointer to the found vertex.
   * @throw std::out_of_range If the vertex is not found.
   */
  VertexPtr needNode(const T &value, const char *msg) const;

  /**
   * @brief Looks for an edge between two vertices in the incident list of u.
   * @param u First vertex.
   * @param v Second vertex.
   * @return Iterator to the found edge, or u->incidentEdges.end() if there is
   * none.
   */
  typename IncidentContainer::iterator
  findEdgeBetween(const VertexPtr &u, const VertexPtr &v) const;

  /**
   * @brief Returns the opposite endpoint of an edge.
   * @param edge The edge.
   * @param from Vertex to move away from.
   * @return Pointer to the other endpoint (equal to from for a loop).
   */
  static VertexNode *otherEnd(const EdgeNode &edge, const VertexNode *from);

  /**
   * @brief Removes an edge from the incident lists of both endpoints.
   * @param edge Edge to unlink. It stays in the global edge list.
   */
  static void unlink(std::shared_ptr<EdgeNode> edge);

  /**
   * @brief Builds the key used for comparing graphs.
   * @return Tuple: vertex count, edge count, sorted vertices, sorted edges.
   */
  Key key() const;

  /**
   * @brief Creates an iterator over incident edges or adjacent vertices.
   * @tparam It Type of the iterator to create.
   * @param v Vertex the iteration is relative to.
   * @param end true for an end iterator, false for a begin iterator.
   * @param rev true for a reverse iterator.
   * @return Iterator of the requested kind.
   * @throw std::out_of_range If vertex v is not in the graph.
   */
  template <typename It> It incidentIt(const T &v, bool end, bool rev) const;

public:
  using size_type = size_t; ///< Type for sizes and degrees.
  using difference_type = std::ptrdiff_t;///< Signed integer type for iterator.
  using reference = T &; ///< Reference to an element (modifiable).
  using const_reference = const T &;///< Const reference to an element (read-only).
  using pointer = T *; ///< Pointer to an element (modifiable).
  using const_pointer = const T *; ///< Pointer to a const element (read-only).

  /** @name Vertex iterators */
  ///@{
  using VertexIterator =
      Iter<IterKind::Vertex, false, false>; ///< Forward vertex iterator.
  using ConstVertexIterator =
      Iter<IterKind::Vertex, true,
           false>; ///< Constant forward vertex iterator.
  using ReverseVertexIterator =
      Iter<IterKind::Vertex, false, true>; ///< Reverse vertex iterator.
  using ConstReverseVertexIterator =
      Iter<IterKind::Vertex, true, true>; ///< Constant reverse vertex iterator.
  ///@}

  /** @name Edge iterators */
  ///@{
  using EdgeIterator =
      Iter<IterKind::Edge, false, false>; ///< Forward edge iterator.
  using ConstEdgeIterator =
      Iter<IterKind::Edge, true, false>; ///< Constant forward edge iterator.
  using ReverseEdgeIterator =
      Iter<IterKind::Edge, false, true>; ///< Reverse edge iterator.
  using ConstReverseEdgeIterator =
      Iter<IterKind::Edge, true, true>; ///< Constant reverse edge iterator.
  ///@}

  /** @name Incident edge iterators */
  ///@{
  using IncidentIterator = Iter<IterKind::Incident, false,
                                false>; ///< Forward incident edge iterator.
  using ConstIncidentIterator =
      Iter<IterKind::Incident, true,
           false>; ///< Constant forward incident edge iterator.
  using ReverseIncidentIterator =
      Iter<IterKind::Incident, false,
           true>; ///< Reverse incident edge iterator.
  using ConstReverseIncidentIterator =
      Iter<IterKind::Incident, true,
           true>; ///< Constant reverse incident edge iterator.
  ///@}

  /** @name Adjacent vertex iterators */
  ///@{
  using AdjacentIterator = Iter<IterKind::Adjacent, false,
                                false>; ///< Forward adjacent vertex iterator.
  using ConstAdjacentIterator =
      Iter<IterKind::Adjacent, true,
           false>; ///< Constant forward adjacent vertex iterator.
  using ReverseAdjacentIterator =
      Iter<IterKind::Adjacent, false,
           true>; ///< Reverse adjacent vertex iterator.
  using ConstReverseAdjacentIterator =
      Iter<IterKind::Adjacent, true,
           true>; ///< Constant reverse adjacent vertex iterator.
  ///@}

  /** @brief Default constructor. Creates an empty graph. */
  Graph() = default;

  /**
   * @brief Copy constructor. Creates a deep copy of the graph.
   * @param other Graph to copy.
   */
  Graph(const Graph &other);

  /** @brief Destructor. */
  ~Graph() = default;

  /**
   * @brief Assignment operator (copy-and-swap).
   * @param other Graph to assign.
   * @return Reference to this graph.
   */
  Graph &operator=(const Graph &other);

  /** @name Comparison operators
   *  Graphs are compared by key: vertex count, edge count, then the sorted
   *  lists of vertices and edges. Insertion order does not affect the result.
   */
  ///@{
  bool operator==(const Graph &other) const {
    return key() == other.key();
  } ///< Equality.
  bool operator!=(const Graph &other) const {
    return !(*this == other);
  } ///< Inequality.
  bool operator<(const Graph &other) const {
    return key() < other.key();
  } ///< Less than.
  bool operator>(const Graph &other) const {
    return other < *this;
  } ///< Greater than.
  bool operator<=(const Graph &other) const {
    return !(other < *this);
  } ///< Less than or equal.
  bool operator>=(const Graph &other) const {
    return !(*this < other);
  } ///< Greater than or equal.
  ///@}

  /** @brief Checks whether the graph is empty (has no vertices). */
  bool empty() const;

  /** @brief Removes all vertices and edges. */
  void clear();

  /**
   * @brief Checks whether a vertex is present.
   * @param v Vertex value.
   * @return true if the vertex is in the graph.
   */
  bool containsVertex(const T &v) const;

  /**
   * @brief Checks whether an edge between two vertices is present.
   * @param u First vertex.
   * @param v Second vertex.
   * @return true if both vertices exist and there is an edge between them.
   */
  bool containsEdge(const T &u, const T &v) const;

  /** @brief Returns the number of vertices. */
  size_type vertexCount() const;

  /** @brief Returns the number of edges. */
  size_type edgeCount() const;

  /**
   * @brief Computes the degree of a vertex (the number of incident edges).
   * @param v Vertex.
   * @return Degree of the vertex.
   * @throw std::out_of_range If the vertex is not in the graph.
   */
  size_type degree(const T &v) const;

  /**
   * @brief Computes the degree of an edge (the number of edges adjacent to it).
   * @param u First endpoint of the edge.
   * @param v Second endpoint of the edge.
   * @return Sum of the endpoint degrees minus 2.
   * @throw std::out_of_range If a vertex is not in the graph.
   * @throw std::invalid_argument If the edge does not exist.
   */
  size_type edgeDegree(const T &u, const T &v) const;

  /**
   * @brief Adds a vertex.
   * @param value Value of the new vertex.
   * @return Iterator to the added vertex.
   * @throw std::invalid_argument If such a vertex already exists.
   */
  VertexIterator addVertex(const T &value);

  /**
   * @brief Adds an edge between two vertices.
   * @param u First endpoint.
   * @param v Second endpoint.
   * @throw std::out_of_range If one of the vertices is missing.
   * @throw std::invalid_argument If u equals v (loop) or the edge already
   * exists.
   */
  void addEdge(const T &u, const T &v);

  /**
   * @brief Removes a vertex by value together with all its edges.
   * @param v Vertex value.
   * @throw std::out_of_range If the vertex is missing.
   */
  void removeVertex(const T &v);

  /**
   * @brief Removes an edge by the values of its endpoints.
   * @param u First endpoint.
   * @param v Second endpoint.
   * @throw std::out_of_range If one of the vertices is missing.
   * @throw std::invalid_argument If the edge does not exist.
   */
  void removeEdge(const T &u, const T &v);

  /**
   * @brief Removes a vertex by iterator together with all its edges.
   * @param pos Iterator to the vertex to remove.
   * @return Iterator to the vertex following the removed one.
   * @throw std::out_of_range If pos is the end iterator.
   */
  VertexIterator eraseVertex(VertexIterator pos);

  /**
   * @brief Removes an edge by iterator.
   * @param pos Iterator to the edge to remove.
   * @return Iterator to the edge following the removed one.
   * @throw std::out_of_range If pos is the end iterator.
   */
  EdgeIterator eraseEdge(EdgeIterator pos);

  /** @name Vertex iterator accessors
   *  Prefixes: c - constant, r - reverse, cr - constant reverse.
   */
  ///@{
  VertexIterator vBegin() {
    return VertexIterator(vertices.begin());
  } ///< Beginning of vertex iteration.
  VertexIterator vEnd() {
    return VertexIterator(vertices.end());
  } ///< End of vertex iteration.
  ConstVertexIterator cvBegin() const {
    return ConstVertexIterator(vertices.begin());
  } ///< Beginning (const).
  ConstVertexIterator cvEnd() const {
    return ConstVertexIterator(vertices.end());
  } ///< End (const).
  ReverseVertexIterator rvBegin() {
    return ReverseVertexIterator(vertices.end());
  } ///< Beginning of reverse iteration.
  ReverseVertexIterator rvEnd() {
    return ReverseVertexIterator(vertices.begin());
  } ///< End of reverse iteration.
  ConstReverseVertexIterator crvBegin() const {
    return ConstReverseVertexIterator(vertices.end());
  } ///< Beginning of reverse iteration (const).
  ConstReverseVertexIterator crvEnd() const {
    return ConstReverseVertexIterator(vertices.begin());
  } ///< End of reverse iteration (const).
  ///@}

  /** @name Edge iterator accessors */
  ///@{
  EdgeIterator eBegin() {
    return EdgeIterator(edges.begin());
  } ///< Beginning of edge iteration.
  EdgeIterator eEnd() {
    return EdgeIterator(edges.end());
  } ///< End of edge iteration.
  ConstEdgeIterator ceBegin() const {
    return ConstEdgeIterator(edges.begin());
  } ///< Beginning (const).
  ConstEdgeIterator ceEnd() const {
    return ConstEdgeIterator(edges.end());
  } ///< End (const).
  ReverseEdgeIterator reBegin() {
    return ReverseEdgeIterator(edges.end());
  } ///< Beginning of reverse iteration.
  ReverseEdgeIterator reEnd() {
    return ReverseEdgeIterator(edges.begin());
  } ///< End of reverse iteration.
  ConstReverseEdgeIterator creBegin() const {
    return ConstReverseEdgeIterator(edges.end());
  } ///< Beginning of reverse iteration (const).
  ConstReverseEdgeIterator creEnd() const {
    return ConstReverseEdgeIterator(edges.begin());
  } ///< End of reverse iteration (const).
  ///@}

  /** @name Incident edge iterator accessors for vertex v
   *  @throw std::out_of_range If vertex v is not in the graph.
   */
  ///@{
  IncidentIterator iBegin(const T &v) {
    return incidentIt<IncidentIterator>(v, false, false);
  } ///< Beginning of iteration.
  IncidentIterator iEnd(const T &v) {
    return incidentIt<IncidentIterator>(v, true, false);
  } ///< End of iteration.
  ConstIncidentIterator ciBegin(const T &v) const {
    return incidentIt<ConstIncidentIterator>(v, false, false);
  } ///< Beginning (const).
  ConstIncidentIterator ciEnd(const T &v) const {
    return incidentIt<ConstIncidentIterator>(v, true, false);
  } ///< End (const).
  ReverseIncidentIterator riBegin(const T &v) {
    return incidentIt<ReverseIncidentIterator>(v, false, true);
  } ///< Beginning of reverse iteration.
  ReverseIncidentIterator riEnd(const T &v) {
    return incidentIt<ReverseIncidentIterator>(v, true, true);
  } ///< End of reverse iteration.
  ConstReverseIncidentIterator criBegin(const T &v) const {
    return incidentIt<ConstReverseIncidentIterator>(v, false, true);
  } ///< Beginning of reverse iteration (const).
  ConstReverseIncidentIterator criEnd(const T &v) const {
    return incidentIt<ConstReverseIncidentIterator>(v, true, true);
  } ///< End of reverse iteration (const).
  ///@}

  /** @name Adjacent vertex iterator accessors for vertex v
   *  @throw std::out_of_range If vertex v is not in the graph.
   */
  ///@{
  AdjacentIterator aBegin(const T &v) {
    return incidentIt<AdjacentIterator>(v, false, false);
  } ///< Beginning of iteration.
  AdjacentIterator aEnd(const T &v) {
    return incidentIt<AdjacentIterator>(v, true, false);
  } ///< End of iteration.
  ConstAdjacentIterator caBegin(const T &v) const {
    return incidentIt<ConstAdjacentIterator>(v, false, false);
  } ///< Beginning (const).
  ConstAdjacentIterator caEnd(const T &v) const {
    return incidentIt<ConstAdjacentIterator>(v, true, false);
  } ///< End (const).
  ReverseAdjacentIterator raBegin(const T &v) {
    return incidentIt<ReverseAdjacentIterator>(v, false, true);
  } ///< Beginning of reverse iteration.
  ReverseAdjacentIterator raEnd(const T &v) {
    return incidentIt<ReverseAdjacentIterator>(v, true, true);
  } ///< End of reverse iteration.
  ConstReverseAdjacentIterator craBegin(const T &v) const {
    return incidentIt<ConstReverseAdjacentIterator>(v, false, true);
  } ///< Beginning of reverse iteration (const).
  ConstReverseAdjacentIterator craEnd(const T &v) const {
    return incidentIt<ConstReverseAdjacentIterator>(v, true, true);
  } ///< End of reverse iteration (const).
  ///@}
};

#include "GraphAlgorithms.ipp"
#include "GraphBasic.ipp"
#include "GraphIterators.ipp"
