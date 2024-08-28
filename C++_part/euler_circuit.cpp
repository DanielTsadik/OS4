#include "euler_circuit.hpp"
#include <vector>
#include <stack>
#include <iostream>

/**
 * @brief Checks if the given graph is connected.
 *
 * This function performs a depth-first search (DFS) starting from the first vertex with an edge.
 * It checks if all vertices that are part of the graph (i.e., have edges) are reachable.
 *
 * @param graph The graph to be checked for connectivity.
 * @return true if the graph is connected or empty, false otherwise.
 */
bool isConnected(const Graph& graph) {
    int vertices = graph.getNumVertices();  // Get the number of vertices in the graph
    std::vector<bool> visited(vertices, false);  // Create a visited array initialized to false
    std::stack<int> stack;  // Stack for DFS

    int startVertex = -1;  // Variable to hold the starting vertex
    for (int i = 0; i < vertices; ++i) {
        if (!graph.getAdjList(i).empty()) {  // Find the first vertex with an edge
            startVertex = i;
            break;
        }
    }

    if (startVertex == -1) return true;  // If no vertex with edges is found, the graph is empty or has no edges

    stack.push(startVertex);  // Push the starting vertex onto the stack

    while (!stack.empty()) {
        int v = stack.top();  // Get the vertex on the top of the stack
        stack.pop();  // Remove the vertex from the stack

        if (!visited[v]) {  // If the vertex has not been visited yet
            visited[v] = true;  // Mark it as visited
            for (int neighbor : graph.getAdjList(v)) {  // Iterate over all adjacent vertices
                if (!visited[neighbor]) {  // If the neighbor has not been visited
                    stack.push(neighbor);  // Push the neighbor onto the stack
                }
            }
        }
    }

    // Check if all vertices with edges have been visited
    for (int i = 0; i < vertices; ++i) {
        if (!graph.getAdjList(i).empty() && !visited[i]) {  // If there's a vertex with edges that hasn't been visited
            return false;  // The graph is not connected
        }
    }

    return true;  // The graph is connected
}

/**
 * @brief Determines if the given graph has an Euler circuit.
 *
 * An Euler circuit exists if the graph is connected and every vertex has an even degree.
 *
 * @param graph The graph to be checked for an Euler circuit.
 * @return true if the graph has an Euler circuit, false otherwise.
 */
bool hasEulerCircuit(const Graph& graph) {
    if (!isConnected(graph)) {  // Check if the graph is connected
        return false;
    }

    // Check if every vertex has an even degree
    for (int i = 0; i < graph.getNumVertices(); ++i) {
        if (graph.getAdjList(i).size() % 2 != 0) {  // If the degree of any vertex is odd
            return false;  // The graph does not have an Euler circuit
        }
    }

    return true;  // The graph has an Euler circuit
}
