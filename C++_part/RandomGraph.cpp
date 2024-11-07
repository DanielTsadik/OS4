#include "graph.hpp"
#include "euler_circuit.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>

/**
 * @brief Generates a random undirected graph with a specified number of edges and vertices.
 *
 * This function generates a random graph by selecting random pairs of vertices to connect
 * with an edge. It ensures that each edge is unique (no duplicate edges) by using a set to store them.
 *
 * @param graph The graph object where the edges will be added.
 * @param numEdges The number of edges to generate.
 * @param numVertices The number of vertices in the graph.
 */
void generateRandomGraph(Graph& graph, int numEdges, int numVertices) {
    std::set<std::pair<int, int>> uniqueEdges;  // Set to keep track of unique edges

    // Generate edges until the desired number of unique edges is reached
    while (uniqueEdges.size() < static_cast<std::set<std::pair<int, int>>::size_type>(numEdges)) {
        int src = rand() % numVertices;  // Randomly select a source vertex
        int dest = rand() % numVertices;  // Randomly select a destination vertex

        if (src != dest) {  // Ensure no self-loops
            auto edge = std::make_pair(std::min(src, dest), std::max(src, dest));  // Order vertices consistently
            if (uniqueEdges.find(edge) == uniqueEdges.end()) {  // If the edge is unique
                uniqueEdges.insert(edge);  // Add the edge to the set
                graph.addEdge(src, dest);  // Add the edge to the graph
            }
        }
    }
}

/**
 * @brief Prints the edges of the graph.
 *
 * This function iterates through the graph and prints out each unique edge.
 * Edges are printed in the format "vertex1 - vertex2".
 *
 * @param graph The graph object whose edges will be printed.
 */
void printEdges(const Graph& graph) {
    std::set<std::pair<int, int>> uniqueEdges;  // Set to keep track of unique edges

    // Iterate over all vertices and their adjacency lists to find edges
    for (int i = 0; i < graph.getNumVertices(); ++i) {
        for (int neighbor : graph.getAdjList(i)) {
            if (i <= neighbor) {  // Ensure each edge is printed only once
                uniqueEdges.insert(std::make_pair(i, neighbor));  // Add the edge to the set
            }
        }
    }

    // Print the unique edges
    std::cout << "Generated Graph:\n";
    for (const auto& edge : uniqueEdges) {
        std::cout << edge.first << " - " << edge.second << std::endl;
    }
}

/**
 * @brief Finds the Euler circuit of a graph if it exists.
 *
 * This function implements a depth-first search (DFS)-based algorithm to find an Euler circuit.
 * The function assumes that the graph is undirected and connected, and that all vertices have an even degree.
 *
 * @param graph The graph object in which to find the Euler circuit.
 * @return A vector of integers representing the Euler circuit, or an empty vector if no Euler circuit exists.
 */
std::vector<int> findEulerCircuit(Graph graph) {
    std::vector<int> circuit;  // Vector to store the Euler circuit
    if (!hasEulerCircuit(graph)) {
        return circuit; // Return an empty vector if no Euler circuit exists
    }

    std::stack<int> path;  // Stack to manage the DFS
    path.push(0); // Start from vertex 0
    int current = 0;

    while (!path.empty()) {
        if (!graph.getAdjList(current).empty()) {  // If current vertex has neighbors
            path.push(current);  // Push the current vertex onto the stack
            int next = graph.getAdjList(current).front();  // Get the next vertex in the adjacency list
            graph.removeEdge(current, next);  // Remove the edge between current and next
            current = next;  // Move to the next vertex
        } else {
            circuit.push_back(current);  // Add the current vertex to the circuit
            current = path.top();  // Backtrack to the previous vertex
            path.pop();  // Pop the top of the stack
        }
    }

    std::reverse(circuit.begin(), circuit.end());  // Reverse the circuit to get the correct order
    return circuit;  // Return the Euler circuit
}

/**
 * @brief Main function to generate a random graph and find its Euler circuit.
 *
 * The main function prompts the user for the number of vertices, edges, and a seed for random number generation.
 * It generates a random graph and then checks if the graph has an Euler circuit. If so, the Euler circuit is printed.
 *
 * @return 0 if the program completes successfully, or 1 if an error occurs.
 */
int main(int argc, char *argv[]) {
    int numEdges = 0, numVertices = 0, seed = 0, opt;

    // Parse command-line options using getopt
    while ((opt = getopt(argc, argv, "v:e:s:")) != -1) {
        switch (opt) {
            case 'v':
                numVertices = std::stoi(optarg);  // convert argument to integer
                break;
            case 'e':
                numEdges = std::stoi(optarg);  // convert argument to integer
                break;
            case 's':
                seed = std::stoi(optarg);  // convert argument to integer
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -v numVertices -e numEdges -s seed\n";
                return 1;
        }
    }

    // Calculate the maximum possible number of edges for the given number of vertices
    int maxEdges = (numVertices * (numVertices - 1)) / 2;

    // Check if the requested number of edges is possible
    if (numEdges > maxEdges) {
        std::cerr << "Number of edges exceeds the maximum possible edges for the given number of vertices." << std::endl;
        return 1;
    }

    srand(seed);  // Set the random seed for edge generation

    Graph graph(numVertices);  // Create a graph with the specified number of vertices
    generateRandomGraph(graph, numEdges, numVertices);  // Generate a random graph with the specified edges
    printEdges(graph);  // Print the edges of the generated graph

    // Check if the graph has an Euler circuit and print it
    if (hasEulerCircuit(graph)) {
        std::cout << "The graph has an Euler circuit.\n";
        std::vector<int> eulerCircuit = findEulerCircuit(graph);
        std::cout << "Euler Circuit: ";
        for (size_t i = 0; i < eulerCircuit.size(); ++i) {
            std::cout << eulerCircuit[i];
            if (i != eulerCircuit.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "The graph does not have an Euler circuit." << std::endl;
    }

    return 0;
}
