#include <iostream>
#include "graph.h"

using namespace std;

void Graph::addEdge(int parent, int child) {
    adjacent[parent].push_back(child); // Add w to node’s list.
}


void Graph::DFS(int node) {

    // Mark the current node as visited and print it
    node_info[node].color = Color::white;
    cout << node << " ";
 
    // Recur for all the vertices adjacent to this vertex
    for (list<int>::iterator i = adjacent[node].begin(); i != adjacent[node].end(); ++i) {
        cout << *i << endl;
        if (!(node_info[*i].color == Color::white))
            DFS(*i);
    }

}