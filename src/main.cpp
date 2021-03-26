#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

/*
int* topologicalSort(int* G){
    // Mark the vertex as visited
    // Visit every child
    // Push vertex to the end of the list
        L.push_back(vertex);

}
*/

/*
list computeDFS(){
    list::int L;
    // Mark all the vertex as white (not visited)
    // For every vertex not visited, call topologicalSort to visit the adjacent vertex
    if(// vertex not visited)
        topologicalSort();
    
    // Return the list
        return L;
}
*/


int main(int argc, const char** argv) {

    int 
        n_dominos,  /* Number of dominos in our graph */ 
        n_edges;  /* Number of edges in our graph */
    
    // Create a graph given in the above diagram
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 9);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(9, 3);
 
    cout << "Following is Depth First Traversal"
            " (starting from vertex 2) \n";
    g.DFS(2);

    cout << endl;
 
    return 0;

}
