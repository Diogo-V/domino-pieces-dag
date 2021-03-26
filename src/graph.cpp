#include <iostream>
#include "graph.h"

using namespace std;

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Add w to v’s list.
}


void Graph::DFS(int v) {
    // Mark the current node as visited and
    // print it
    visited[v] = true;
    cout << v << " ";
 
    // Recur for all the vertices adjacent
    // to this vertex
    for (list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i);
}