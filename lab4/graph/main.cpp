/**
 * @file main.cpp
 * @brief Interactive console menu for testing the Graph class.
 */
#include "Graph.hpp"
#include <iostream>
#include <limits>
#include <string>

using G = Graph<int>;

/**
 * @brief Reads an integer with input validation.
 * @param prompt Input prompt.
 * @return The entered integer.
 */
int readInt(const std::string &prompt) {
  int num;
  while (true) {
    std::cout << prompt;
    if (std::cin >> num)
      return num;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter an integer.\n";
  }
}

/** @brief Prints the list of menu items. */
void printMenu() {
  std::cout << "\n===== MENU =====\n"
            << " 1  - add vertex\n"
            << " 2  - add edge\n"
            << " 3  - remove vertex (by value)\n"
            << " 4  - remove edge (by value)\n"
            << " 5  - check if vertex exists\n"
            << " 6  - check if edge exists\n"
            << " 7  - number of vertices and edges\n"
            << " 8  - vertex degree\n"
            << " 9  - edge degree\n"
            << " 10 - iterate over vertices (forward/reverse/const)\n"
            << " 11 - iterate over edges (forward/reverse/const)\n"
            << " 12 - edges incident to a vertex\n"
            << " 13 - vertices adjacent to a vertex\n"
            << " 14 - erase vertex by iterator (by position index)\n"
            << " 15 - erase edge by iterator (by position index)\n"
            << " 16 - copy and compare graphs\n"
            << " 17 - print graph\n"
            << " 18 - clear graph\n"
            << " 0  - exit\n";
}

/**
 * @brief Prints vertices using forward, reverse, constant and constant reverse
 * iterators.
 * @param graph Graph.
 */
void showVertices(G &graph) {
  std::cout << "forward:   ";
  for (auto it = graph.vBegin(); it != graph.vEnd(); ++it)
    std::cout << *it << " ";
  std::cout << "\nreverse:   ";
  for (auto it = graph.rvBegin(); it != graph.rvEnd(); ++it)
    std::cout << *it << " ";
  std::cout << "\nconst:     ";
  for (auto it = graph.cvBegin(); it != graph.cvEnd(); ++it)
    std::cout << *it << " ";
  std::cout << "\nconst rev: ";
  for (auto it = graph.crvBegin(); it != graph.crvEnd(); ++it)
    std::cout << *it << " ";
  std::cout << "\n";
}

/**
 * @brief Prints edges using forward, reverse, constant and constant reverse
 * iterators.
 * @param graph Graph.
 */
void showEdges(G &graph) {
  std::cout << "forward:   ";
  for (auto it = graph.eBegin(); it != graph.eEnd(); ++it)
    std::cout << "(" << it->first << "," << it->second << ") ";
  std::cout << "\nreverse:   ";
  for (auto it = graph.reBegin(); it != graph.reEnd(); ++it)
    std::cout << "(" << it->first << "," << it->second << ") ";
  std::cout << "\nconst:     ";
  for (auto it = graph.ceBegin(); it != graph.ceEnd(); ++it)
    std::cout << "(" << it->first << "," << it->second << ") ";
  std::cout << "\nconst rev: ";
  for (auto it = graph.creBegin(); it != graph.creEnd(); ++it)
    std::cout << "(" << it->first << "," << it->second << ") ";
  std::cout << "\n";
}

/**
 * @brief Prints edges incident to a vertex using all four iterator variants.
 * @param graph Graph.
 * @param v Vertex value.
 */
void showIncident(G &graph, int v) {
  std::cout << "forward:   ";
  for (auto it = graph.iBegin(v); it != graph.iEnd(v); ++it)
    std::cout << "(" << it->first << "," << it->second << ") ";
  std::cout << "\nreverse:   ";
  for (auto it = graph.riBegin(v); it != graph.riEnd(v); ++it)
    std::cout << "(" << it->first << "," << it->second << ") ";
  std::cout << "\nconst:     ";
  for (auto it = graph.ciBegin(v); it != graph.ciEnd(v); ++it)
    std::cout << "(" << it->first << "," << it->second << ") ";
  std::cout << "\nconst rev: ";
  for (auto it = graph.criBegin(v); it != graph.criEnd(v); ++it)
    std::cout << "(" << it->first << "," << it->second << ") ";
  std::cout << "\n";
}

/**
 * @brief Prints vertices adjacent to a vertex using all four iterator variants.
 * @param graph Graph.
 * @param v Vertex value.
 */
void showAdjacent(G &graph, int v) {
  std::cout << "forward:   ";
  for (auto it = graph.aBegin(v); it != graph.aEnd(v); ++it)
    std::cout << *it << " ";
  std::cout << "\nreverse:   ";
  for (auto it = graph.raBegin(v); it != graph.raEnd(v); ++it)
    std::cout << *it << " ";
  std::cout << "\nconst:     ";
  for (auto it = graph.caBegin(v); it != graph.caEnd(v); ++it)
    std::cout << *it << " ";
  std::cout << "\nconst rev: ";
  for (auto it = graph.craBegin(v); it != graph.craEnd(v); ++it)
    std::cout << *it << " ";
  std::cout << "\n";
}

/**
 * @brief Program entry point. Runs the menu loop until the user chooses exit.
 * @return 0 on normal termination.
 */
int main() {
  G graph;
  G copy;
  bool hasCopy = false;

  while (true) {
    printMenu();
    int choose = readInt("Your choice: ");
    if (choose == 0)
      break;

    try {
      switch (choose) {
      case 1: {
        int v = readInt("Vertex value: ");
        graph.addVertex(v);
        std::cout << "Vertex added.\n";
        break;
      }
      case 2: {
        int u = readInt("First vertex: ");
        int v = readInt("Second vertex: ");
        graph.addEdge(u, v);
        std::cout << "Edge added.\n";
        break;
      }
      case 3: {
        graph.removeVertex(readInt("Vertex to remove: "));
        std::cout << "Vertex removed.\n";
        break;
      }
      case 4: {
        int u = readInt("First vertex: ");
        int v = readInt("Second vertex: ");
        graph.removeEdge(u, v);
        std::cout << "Edge removed.\n";
        break;
      }
      case 5:
        std::cout << (graph.containsVertex(readInt("Vertex: ")) ? "Yes" : "No")
                  << "\n";
        break;
      case 6: {
        int u = readInt("First vertex: ");
        int v = readInt("Second vertex: ");
        std::cout << (graph.containsEdge(u, v) ? "Yes" : "No") << "\n";
        break;
      }
      case 7:
        std::cout << "Vertices: " << graph.vertexCount()
                  << ", edges: " << graph.edgeCount() << "\n";
        break;
      case 8:
        std::cout << "Degree: " << graph.degree(readInt("Vertex: ")) << "\n";
        break;
      case 9: {
        int u = readInt("First vertex: ");
        int v = readInt("Second vertex: ");
        std::cout << "Edge degree: " << graph.edgeDegree(u, v) << "\n";
        break;
      }
      case 10:
        showVertices(graph);
        break;
      case 11:
        showEdges(graph);
        break;
      case 12:
        showIncident(graph, readInt("Vertex: "));
        break;
      case 13:
        showAdjacent(graph, readInt("Vertex: "));
        break;
      case 14: {
        std::cout << graph << "\n";
        int idx = readInt("Vertex position in the list (from 0): ");
        if (idx < 0 || (size_t)idx >= graph.vertexCount()) {
          std::cout << "Invalid index.\n";
          break;
        }
        auto it = graph.vBegin();
        for (int i = 0; i < idx; ++i)
          ++it;
        auto next = graph.eraseVertex(it);
        std::cout << "Erased. ";
        if (next != graph.vEnd())
          std::cout << "Next vertex: " << *next << "\n";
        else
          std::cout << "No next vertex (end).\n";
        break;
      }
      case 15: {
        std::cout << graph << "\n";
        int idx = readInt("Edge position in the list (from 0): ");
        if (idx < 0 || (size_t)idx >= graph.edgeCount()) {
          std::cout << "Invalid index.\n";
          break;
        }
        auto it = graph.eBegin();
        for (int i = 0; i < idx; ++i)
          ++it;
        auto next = graph.eraseEdge(it);
        std::cout << "Erased. ";
        if (next != graph.eEnd())
          std::cout << "Next edge: (" << next->first << "," << next->second
                    << ")\n";
        else
          std::cout << "No next edge (end).\n";
        break;
      }
      case 16: {
        if (!hasCopy) {
          copy = graph;
          hasCopy = true;
          std::cout
              << "A copy of the current graph has been saved.\n"
              << "Modify the graph and choose this item again to compare.\n";
        } else {
          std::cout << "copy:  " << copy << "\ngraph: " << graph << "\n";
          std::cout << "copy==graph: " << (copy == graph) << "\n"
                    << "copy!=graph: " << (copy != graph) << "\n"
                    << "copy<graph:  " << (copy < graph) << "\n"
                    << "copy>graph:  " << (copy > graph) << "\n";
          hasCopy = false;
        }
        break;
      }
      case 17:
        std::cout << graph << "\n";
        break;
      case 18:
        graph.clear();
        std::cout << "Graph cleared, empty(): " << graph.empty() << "\n";
        break;
      default:
        std::cout << "No such menu item.\n";
      }
    } catch (const std::exception &error) {
      std::cout << "Error: " << error.what() << "\n";
    }
  }
  return 0;
}