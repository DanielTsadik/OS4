#include "graph.hpp"

Graph::Graph(int vertices) : numVertices(vertices), adjList(vertices) {}

void Graph::addEdge(int src, int dest) {
    adjList[src].push_back(dest);
    adjList[dest].push_back(src);
}

void Graph::removeEdge(int src, int dest) {
    adjList[src].remove(dest);
    adjList[dest].remove(src);
}

int Graph::getNumVertices() const {
    return numVertices;
}

const std::list<int>& Graph::getAdjList(int vertex) const {
    return adjList[vertex];
}
