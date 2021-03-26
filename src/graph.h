#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>

using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
class Graph {
    
    public:
        map<int, bool> visited;
        map<int, list<int>> adj;
    
        // function to add an edge to graph
        void addEdge(int v, int w);
    
        // DFS traversal of the vertices
        // reachable from v
        void DFS(int v);
};

#endif // GRAPH