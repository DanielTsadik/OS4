#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <list>
#include <iostream>

class Graph {
private:
    int numVertices;
    std::vector<std::list<int>> adjList;

public:
    Graph(int vertices);
    void addEdge(int src, int dest);
    void removeEdge(int src, int dest);
    int getNumVertices() const;
    const std::list<int>& getAdjList(int vertex) const;
};

#endif // GRAPH_HPP
