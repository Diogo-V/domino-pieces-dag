#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <string>


using namespace std;


/**
 * @brief Represents a node's color. Used mainly during DFS.
 * 
 * @param white node has not been reached 
 * @param grey node has been reached but not closed 
 * @param black node has been closed
 */
enum class Color { white, black, grey };


/**
 * @brief Holds DFS information about the related node.
 * 
 * @param start_time int value representing the time of discovery of this node
 * @param finish_time int value representing the time of closing of this node
 * @param color represents the current state of the node
 */
typedef struct {
    int start_time;
    int finish_time;
    Color color;
} node_info_struct;


/**
 * @brief Represents a Directed Acyclic Graph. Uses adjacency list.
 */
class Graph {
    
    private:

        /**
         * @brief Holds all the info related to the key node after DFS traversal.
         */
        map<int, node_info_struct> _nodeInfo;

        /**
         * @brief Holds all the nodes which this node leads to.
         */
        map<int, list<int>> _adjacent;
    
    public:

        /**
         * @brief Get the Node Info object.
         * 
         * @param node node value
         * @return node_info_struct related to this node
         */
        node_info_struct getNodeInfo(int node);

        /**
         * @brief Get the Adjacent Nodes object.
         * 
         * @param node node value
         * @return list<int> representing a list of connected nodes
         */
        list<int> getAdjacentNodes(int node);
        
        /**
         * @brief Changes node's starting time.
         * 
         * @param node node to be changed
         * @param start_time new value
         */
        void setNodeStartTime(int node, int start_time);

        /**
         * @brief Changes node's closing time.
         * 
         * @param node node to be changed
         * @param finish_time new value
         */
        void setNodeFinishTime(int node, int finish_time);

        /**
         * @brief Changes node's current color.
         * 
         * @param node node to be changed
         * @param color new color
         */
        void setNodeColor(int node, Color color);

        /**
         * @brief Inserts a new edge from parent to child node.
         * 
         * @param parent parent's node
         * @param child child's node
         */
        void addEdge(int parent, int child);
    
        /**
         * @brief Performs a DFS traversal of this graph starting from root node.
         * 
         * @param root starting point for DFS traversal
         */
        void DFS(int root);

};


#endif // GRAPH_H
