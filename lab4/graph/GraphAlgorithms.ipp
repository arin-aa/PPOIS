/**
 * @file GraphAlgorithms.ipp
 * @brief Implementation of edge degree computation, the graph comparison key
 * and stream output of a graph.
 *
 * Methods of the class are documented in Graph.hpp.
 */
#pragma once
#include "Graph.hpp"

template <typename T>
typename Graph<T>::size_type Graph<T>::edgeDegree(const T &u,
                                                  const T &v) const {
  auto un = needNode(u, "vertex u not found");
  auto vn = needNode(v, "vertex v not found");
  if (findEdgeBetween(un, vn) == un->incidentEdges.end()) {
    throw std::invalid_argument("edge not found");
  }
  return un->incidentEdges.size() + vn->incidentEdges.size() - 2;
}

template <typename T> typename Graph<T>::Key Graph<T>::key() const {
  std::vector<T> vspis;
  std::vector<std::pair<T, T>> espis;
  for (const auto &ver : vertices) {
    vspis.push_back(ver->value);
  }
  for (const auto &edg : edges) {
    auto weaku = edg->u;
    auto weakv = edg->v;
    auto sharedu = weaku.lock();
    auto sharedv = weakv.lock();
    auto a = sharedu->value;
    auto b = sharedv->value;
    espis.push_back(a < b ? std::make_pair(a, b) : std::make_pair(b, a));
  }
  std::sort(vspis.begin(), vspis.end());
  std::sort(espis.begin(), espis.end());
  return Key(vertices.size(), edges.size(), std::move(vspis), std::move(espis));
}

/**
 * @brief Writes a graph to a stream as Graph{ vertices=[...], edges=[(a,b),
 * ...] }.
 * @tparam U Vertex value type.
 * @param os Output stream.
 * @param graph Graph to print.
 * @return Reference to os.
 */
template <typename U>
std::ostream &operator<<(std::ostream &os, const Graph<U> &graph) {
  os << "Graph{ vertices=[";
  bool first = true;
  std::for_each(graph.cvBegin(), graph.cvEnd(), [&](const U &vertex) {
    if (!first)
      os << ", ";
    first = false;
    os << vertex;
  });
  os << "], edges=[";
  first = true;
  std::for_each(graph.ceBegin(), graph.ceEnd(),
                [&](const std::pair<U, U> &edge) {
                  if (!first)
                    os << ", ";
                  first = false;
                  os << "(" << edge.first << "," << edge.second << ")";
                });
  return os << "] }";
}
