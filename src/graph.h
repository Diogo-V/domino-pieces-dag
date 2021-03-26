#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
#include <string>


using namespace std;


enum class Color { white, black, grey };


typedef struct {
    int start_time;
    int finish_time;
    Color color;
} node_info_struct;


// Graph class represents a directed graph
// using adjacency list representation
class Graph {
    
    public:

        map<int, node_info_struct> node_info;
        map<int, list<int>> adjacent;
    
        // function to add an edge to graph
        void addEdge(int v, int w);
    
        // DFS traversal of the vertices
        // reachable from v
        void DFS(int v);
};


#endif // GRAPH
