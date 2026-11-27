/**
 * @file GraphBasic.ipp
 * @brief Implementation of the core Graph methods: search, adding and removing
 * vertices and edges, copy constructor and assignment operator.
 *
 * The methods themselves are documented in Graph.hpp.
 */
#pragma once
#include "Graph.hpp"

template <typename T>
typename Graph<T>::VertexPtr Graph<T>::findNode(const T &value) const {
  auto it =
      std::find_if(vertices.begin(), vertices.end(),
                   [&](const VertexPtr &vert) { return vert->value == value; });
  return it == vertices.end() ? nullptr : *it;
}

template <typename T>
typename Graph<T>::VertexPtr Graph<T>::needNode(const T &value,
                                                const char *msg) const {
  auto res = findNode(value);
  if (!res) {
    throw std::out_of_range(msg);
  }
  return res;
}

template <typename T>
typename Graph<T>::VertexNode *Graph<T>::otherEnd(const EdgeNode &edge,
                                                  const VertexNode *from) {
  auto firstVertPtr = edge.u.lock();
  auto secondVertPtr = edge.v.lock();

  auto firstVert = firstVertPtr.get();
  auto secondVert = secondVertPtr.get();
  return firstVert == from ? secondVert : firstVert;
}

template <typename T>
typename Graph<T>::IncidentContainer::iterator
Graph<T>::findEdgeBetween(const VertexPtr &u, const VertexPtr &v) const {
  return std::find_if(u->incidentEdges.begin(), u->incidentEdges.end(),
                      [&](const std::shared_ptr<EdgeNode> &edge) {
                        return otherEnd(*edge, u.get()) == v.get();
                      });
}

template <typename T> void Graph<T>::unlink(std::shared_ptr<EdgeNode> edge) {
  auto a = edge->u.lock();
  auto b = edge->v.lock();
  a->incidentEdges.remove(edge);
  b->incidentEdges.remove(edge);
}

template <typename T>
template <typename It>
It Graph<T>::incidentIt(const T &v, bool end, bool rev) const {
  auto needVer = needNode(v, "vertex not found");
  return It((end != rev) ? needVer->incidentEdges.end()
                         : needVer->incidentEdges.begin(),
            needVer.get());
}

template <typename T> Graph<T>::Graph(const Graph &other) {
  for (auto &vert : other.vertices) {
    addVertex(vert->value);
  }
  for (auto &edg : other.edges) {
    auto sharedu = edg->u.lock();
    auto sharedv = edg->v.lock();
    addEdge(sharedu->value, sharedv->value);
  }
}

template <typename T> Graph<T> &Graph<T>::operator=(const Graph &other) {
  if (this != &other) {
    Graph graph(other);
    vertices.swap(graph.vertices);
    edges.swap(graph.edges);
  }
  return *this;
}

template <typename T> bool Graph<T>::empty() const { return vertices.empty(); }

template <typename T> void Graph<T>::clear() {
  vertices.clear();
  edges.clear();
}

template <typename T>
typename Graph<T>::size_type Graph<T>::vertexCount() const {
  return vertices.size();
}

template <typename T> typename Graph<T>::size_type Graph<T>::edgeCount() const {
  return edges.size();
}

template <typename T> bool Graph<T>::containsVertex(const T &v) const {
  return findNode(v) != nullptr;
}

template <typename T>
bool Graph<T>::containsEdge(const T &u, const T &v) const {
  auto needU = findNode(u);
  auto needV = findNode(v);
  return needU && needV &&
         findEdgeBetween(needU, needV) != needU->incidentEdges.end();
}

template <typename T>
typename Graph<T>::size_type Graph<T>::degree(const T &v) const {
  return needNode(v, "vertex not found")->incidentEdges.size();
}

template <typename T>
typename Graph<T>::VertexIterator Graph<T>::addVertex(const T &value) {
  if (findNode(value)) {
    throw std::invalid_argument("duplicate vertex");
  }
  auto node = std::make_shared<VertexNode>();
  node->value = value;
  vertices.push_back(node);
  return VertexIterator(std::prev(vertices.end()));
}

template <typename T> void Graph<T>::addEdge(const T &u, const T &v) {
  auto needU = needNode(u, "vertex u not found");
  auto needV = needNode(v, "vertex v not found");
  if (findEdgeBetween(needU, needV) != needU->incidentEdges.end()) {
    throw std::invalid_argument("parallel edge not allowed");
  }
  auto node = std::make_shared<EdgeNode>();
  node->u = needU;
  node->v = needV;
  needU->incidentEdges.push_back(node);
  needV->incidentEdges.push_back(node);
  edges.push_back(node);
}

template <typename T>
typename Graph<T>::VertexIterator Graph<T>::eraseVertex(VertexIterator pos) {
  if (pos.position == vertices.end()) {
    throw std::out_of_range("cannot erase the end iterator");
  }
  auto node = *pos.position;
  while (!node->incidentEdges.empty()) {
    auto edg = node->incidentEdges.front();
    unlink(edg);
    edges.remove(edg);
  }
  auto nextVertex = vertices.erase(pos.position);
  return VertexIterator(nextVertex);
}

template <typename T>
typename Graph<T>::EdgeIterator Graph<T>::eraseEdge(EdgeIterator pos) {
  if (pos.position == edges.end()) {
    throw std::out_of_range("cannot erase the end iterator");
  }
  unlink(*pos.position);
  auto nextEdge = edges.erase(pos.position);
  return EdgeIterator(nextEdge);
}

template <typename T> void Graph<T>::removeVertex(const T &v) {
  auto needV = needNode(v, "vertex not found");
  eraseVertex(
      VertexIterator(std::find(vertices.begin(), vertices.end(), needV)));
}

template <typename T> void Graph<T>::removeEdge(const T &u, const T &v) {
  auto needU = needNode(u, "vertex u not found");
  auto needV = needNode(v, "vertex v not found");
  auto needE = findEdgeBetween(needU, needV);
  if (needE == needU->incidentEdges.end()) {
    throw std::invalid_argument("edge not found");
  }
  eraseEdge(EdgeIterator(std::find(edges.begin(), edges.end(), *needE)));
}
