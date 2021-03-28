#include <iostream>
#include <string>
#include "graph.h"


using namespace std;


/**
 * @brief Inits a graph with all the required space to insert nodes. After init, is still empty.
 *
 * @return newly created graph
 */
Graph initGraph() {

    /* Receive number of nodes and vertices from cin */
    int n_nodes, n_edges;

    /* Used in loops to gather line */
    string line;

    /* Gets first line from file which holds graph inputs */
    std::getline(cin, line);
    sscanf(line.c_str(), "%d %d", &n_nodes, &n_edges);

    /* Creates graph */
    Graph graph(n_nodes);

    return graph;

}


/**
 * @brief Populates graph with all the nodes + edges from cin.
 *
 * @param graph Graph to be populated
 */
void populatesGraph(Graph *graph) {

    /* Hold parent and child node numbers */
    int parent, child;

    /* Populates graph */
    for(string line; getline(cin, line); ) {
        sscanf(line.c_str(), "%d %d", &parent, &child);
        (*graph).addEdge(parent, child);
    }

}


/**
 * @brief Counts number os times we have to make a piece fall to traverse all the pieces (is just
 *        the amount of node with in degree 0). Also finds longest path in our graph
 *
 * @param graph graph representing domino problem which will be traversed
 * @param topological stack with nodes in topological order
 */
void solveDominoPiecesProblem(Graph* graph, stack<int>* topological) {

    /* Hold the amount of times we have to make a piece fall to traverse all the pieces */
    int interventions = 0, sequence = 0;

    /* Counts number of nodes with in degree 0 (interventions) and sets their distance as 1. This
     * will be used later on when we try to find the longest path */
    for (int node = 1; node <= graph->getNumberOfNodes(); node++) {
        if (graph->getNodeInfo(node).inDegree == 0) {
            interventions++;
            graph->setNodeDP(node, 1);
        }
    }

    /* We traverse all the nodes in our topological stack and traverse them one by one. While doing
     * this, we traverse their children and change their distance. This will count the number of
     * edges between them and their parents */
    while ( ! topological->empty()) {

        /* Gets node from stack */
        int node = topological->top(); topological->pop();

        /* Traverses children sets their distance */
        if (graph->getNodeInfo(node).dist != INT_MIN) {

            int parentDist = graph->getNodeInfo(node).dist;

            for (auto child: graph->getAdjacentNodes(node)) {

                if (graph->getNodeInfo(child).dist < parentDist + 1) {

                    graph->setNodeDP(child, parentDist + 1);
                    if (parentDist + 1 > sequence)  /* Finds and holds longest distance */
                        sequence = parentDist + 1;

                }

            }

        }

    }

    /* Outputs final result */
    cout << interventions << " " << sequence << endl;

}


/**
 * @brief Driver code.
 *
 * @return terminate code
 */
int main() {

    /* Creates the graph which is going to represent all the domino pieces' placement */
    Graph graph = initGraph();

    /* Populates graph with all the nodes and edges from stdin */
    populatesGraph(&graph);

    /* Performs a DFS and returns an array with all the vertices inversely sorted by finish time */
    stack<int> topological = graph.DFS();

    /* Finds minimum interventions and biggest sequence. Prints them on the screen */
    solveDominoPiecesProblem(&graph, &topological);

    exit(EXIT_SUCCESS);

}
