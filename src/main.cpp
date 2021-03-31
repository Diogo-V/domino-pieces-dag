#include <iostream>
#include <string>
#include "graph.h"


using namespace std;


/**
 * @brief Creates and populates the graph that is going to represent all the pieces' placement.
 *
 * @return newly created graph
 */
Graph initGraph() {

    /* Receive number of nodes and vertices from cin */
    int nNodes, nEdges;

    /* Hold parent and child node numbers while populating */
    int parent, child;

    /* Reads number of nodes and edges from cin */
    cin >> nNodes >> nEdges;

    /* Creates graph */
    Graph graph(nNodes);

    /* Populates graph with all the edges from cin */
    for (int i = 0; i < nEdges; i++) {
        cin >> parent >> child;
        graph.addEdge(parent, child);
    }

    return graph;

}


/**
 * @brief Counts number os times we have to make a piece fall to traverse all the pieces (is just
 *        the amount of node with in degree 0). Also finds longest path in our graph
 *
 * @param graph graph representing domino problem which will be traversed
 * @param topological stack with nodes in topological order
 */
void solveDominoPiecesProblem(Graph* graph, deque<int>* topological) {

    /* Hold the amount of times we have to make a piece fall to traverse all the pieces */
    int interventions = 0, sequence = 0;

    /* Counts number of nodes with in degree 0 (interventions) and sets their distance as 1. This
     * will be used later on when we try to find the longest path */
    for (int node = 1; node <= graph->getNumberOfNodes(); node++) {
        if (graph->getNodeInfo(node).inDegree == 0) {
            interventions++;
            graph->setNodeDistance(node, 1);
        }
    }

    /* We traverse all the nodes in our topological stack and traverse them one by one. While doing
     * this, we traverse their children and change their distance. This will count the number of
     * edges between them and their parents */
    while ( ! topological->empty()) {

        /* Gets node from stack */
        int node = topological->front(); topological->pop_front();

        /* Traverses children sets their distance */
        if (graph->getNodeInfo(node).dist != NEGATIVE_INFINITY) {

            int parentDist = graph->getNodeInfo(node).dist;

            for (auto child: graph->getAdjacentNodes(node)) {

                if (graph->getNodeInfo(child).dist < parentDist + 1) {

                    graph->setNodeDistance(child, parentDist + 1);

                    /* Finds and holds longest distance. Is done here as to avoid doing another loop
                     * to find the highest distance */
                    if (parentDist + 1 > sequence) sequence = parentDist + 1;

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

    /* Creates and populates the graph that is going to represent all the pieces' placement */
    Graph graph = initGraph();

    /* Performs a DFS and returns an array with all the vertices inversely sorted by finish time */
    deque<int> topological = graph.dfs();

    /* Finds minimum interventions and biggest sequence. Prints them on the screen */
    solveDominoPiecesProblem(&graph, &topological);

    exit(EXIT_SUCCESS);

}
