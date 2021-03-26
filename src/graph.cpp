#include <iostream>
#include "graph.h"


using namespace std;


/**
 * @brief Inserts a new edge from parent to child node.
 * 
 * @param parent parent's node
 * @param child child's node
 */
void Graph::addEdge(int parent, int child) {
    _adjacent[parent].push_back(child); // Add w to node’s list.
}


/**
 * @brief Performs a DFS traversal of this graph starting from root node.
 * 
 * @param root starting point for DFS traversal
 */
void Graph::DFS(int node) {
    
    for (list<int>::iterator i = this->getAdjacentNodes(node).begin(); i != this->getAdjacentNodes(node).end(); ++i) {
        if (!(this->getNodeInfo(*i).color == Color::white))
            DFS(*i);
    }

}


/**
 * @brief Get the Node Info object.
 * 
 * @param node node value
 * @return node_info_struct related to this node
 */
node_info_struct Graph::getNodeInfo(int node) { 
    return this->_nodeInfo[node]; 
}


/**
 * @brief Get the Adjacent Nodes object.
 * 
 * @param node node value
 * @return list<int> representing a list of connected nodes
 */
list<int> Graph::getAdjacentNodes(int node) { 
    return this->_adjacent[node];
}


/**
 * @brief Changes node's starting time.
 * 
 * @param node node to be changed
 * @param start_time new value
 */
void Graph::setNodeStartTime(int node, int start_time) {
    this->_nodeInfo[node].start_time = start_time;
}


/**
 * @brief Changes node's closing time.
 * 
 * @param node node to be changed
 * @param finish_time new value
 */
void Graph::setNodeFinishTime(int node, int finish_time) {
    this->_nodeInfo[node].finish_time = finish_time;
}


/**
 * @brief Changes node's current color.
 * 
 * @param node node to be changed
 * @param color new color
 */
void Graph::setNodeColor(int node, Color color) {
    this->_nodeInfo[node].color = color;
}
