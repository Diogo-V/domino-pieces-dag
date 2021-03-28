#include <iostream>
#include "graph.h"


using namespace std;


/**
 * @brief Graph constructor.
 *
 * @param nodes number of nodes inside graph
 */
Graph::Graph(int nodes) {

    /* Populates info vector with all the possible nodes */
    nodeInfoStruct info;
    for (int i = 1; i <= nodes; i++)
        this->_nodeInfo.insert(make_pair(i, info));

    /* Saves number of nodes */
    this->_numberOfNodes = nodes;

}


/**
 * @brief Get the Node Info object.
 * 
 * @param node node value
 * @return nodeInfoStruct related to this node
 */
nodeInfoStruct Graph::getNodeInfo(int node) { return this->_nodeInfo[node]; }


/**
 * @brief Get the Adjacent Nodes object.
 * 
 * @param node node value
 * @return list<int> representing a list of connected nodes
 */
list<int> Graph::getAdjacentNodes(int node) { return this->_adjacent[node]; }


/**
 * @brief Get the Number of Nodes object.
 *
 * @return number of nodes
 */
int Graph::getNumberOfNodes() const { return this->_numberOfNodes; }


/**
 * @brief Changes node's current color.
 * 
 * @param node node to be changed
 * @param color new color
 */
void Graph::setNodeColor(int node, Color color) { this->_nodeInfo[node].color = color; }


/**
 * @brief Increments node's total in degree value.
 *
 * @param node node to be changed
 */
void Graph::incrementNodeInDegree(int node) { this->_nodeInfo[node].inDegree++; }


/**
 * @brief Changes node's distance.
 *
 * @param node node to be changed
 * @param dp new distance
 */
void Graph::setNodeDP(int node, int dp) { this->_nodeInfo[node].dist = dp; }


/**
 * @brief Inserts a new edge from parent to child node.
 *
 * @param parent parent's node
 * @param child child's node
 */
void Graph::addEdge(int parent, int child) {

    /* Creates a connection between two nodes */
    this->_adjacent[parent].push_back(child);

    /* Increments child's in degrees */
    this->incrementNodeInDegree(child);

}


/**
 * @brief Performs a DFS traversal of this graph starting from first node.
 *
 * @return list with nodes in topological order
 */
stack<int> Graph::DFS() {

    /* Holds an list of inversely sorted nodes by their finish time */
    stack<int> topological;

    /* Cycles through each node and performs a DFS on it */
    for (int parent = 1; parent <= this->getNumberOfNodes(); parent++)
        if (this->getNodeInfo(parent).color == Color::white)
            this->DFS_visit(parent, &topological);

    return topological;

}


/**
 * @brief Auxiliary function for DFS. Performs DFS from this node onward.
 *
 * @param parent root for DFS
 * @param topological stack with nodes in topological order
 */
void Graph::DFS_visit(int parent, stack<int>* topological) {

    /* Fail safe */
    assert(this->getNodeInfo(parent).color == Color::white);

    /* Since we have visited this node, we mark it as grey and save time of discovery */
    this->setNodeColor(parent, Color::grey);

    /* Cycles through all parent's edges and performs DFS_visit on all of them */
    for (int child : this->getAdjacentNodes(parent))
        if (this->getNodeInfo(child).color == Color::white)
            this->DFS_visit(child, topological);

    /* Since we have finished visiting this node, we mark it as black and save time of ending */
    this->setNodeColor(parent, Color::black);
    topological->push(parent);

}
