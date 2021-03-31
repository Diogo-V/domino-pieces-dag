#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <string>
#define NEGATIVE_INFINITY INT_MIN


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
 * @brief Holds information about the related node.
 * 
 * @param color represents the current state of the node
 * @param inDegree holds the amount of nodes connected to this node
 * @param dp holds distance
 */
typedef struct nodeInfoStruct {
    Color color;
    int inDegree;
    int dist;
    nodeInfoStruct() {
        color = Color::white;
        inDegree = 0;
        dist = NEGATIVE_INFINITY;
    };
} nodeInfoStruct;


/**
 * @brief Represents a Directed Acyclic Graph. Uses adjacency list.
 */
class Graph {
    
    private:

        /**
         * @brief Holds all the info related to the key node after DFS traversal.
         */
        vector<nodeInfoStruct> _nodeInfo;

        /**
         * @brief Holds all the nodes which this node leads to.
         */
        vector<list<int>> _adjacent;

        /**
         * @brief Holds number of vertices inside this graph.
         */
        int _numberOfNodes;
    
    public:

        /**
         * @brief Graph constructor.
         *
         * @param nodes number of nodes inside graph
         */
        explicit Graph(int nodes);

        /**
         * @brief Get the Node Info object.
         * 
         * @param node node value
         * @return nodeInfoStruct related to this node
         */
        nodeInfoStruct getNodeInfo(int node);

        /**
         * @brief Get the Adjacent Nodes object.
         * 
         * @param node node value
         * @return list<int> representing a list of connected nodes
         */
        list<int> getAdjacentNodes(int node);

        /**
         * @brief Get the Number of Nodes object.
         *
         * @return number of nodes
         */
        int getNumberOfNodes() const;

        /**
         * @brief Changes node's current color.
         * 
         * @param node node to be changed
         * @param color new color
         */
        void setNodeColor(int node, Color color);

        /**
         * @brief Increments node's total in degree value.
         *
         * @param node node to be changed
         */
        void incrementNodeInDegree(int node);

        /**
         * @brief Changes node's distance.
         *
         * @param node node to be changed
         * @param dist new distance
         */
        void setNodeDistance(int node, int dist);

        /**
         * @brief Inserts a new edge from parent to child node.
         * 
         * @param parent parent's node
         * @param child child's node
         */
        void addEdge(int parent, int child);

        /**
         * @brief Performs an iterative DFS traversal of this graph starting from first node (1).
         *
         * @return deque with nodes in topological order
         */
        deque<int> dfs();

};


#endif // GRAPH_H
