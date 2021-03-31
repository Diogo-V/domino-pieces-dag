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
    this->_nodeInfo.resize(nodes, info);

    /* Creates and allocates space for all the nodes' connections */
    this->_adjacent.resize(nodes);

    /* Saves number of nodes */
    this->_numberOfNodes = nodes;

}


/**
 * @brief Get the Node Info object.
 * 
 * @param node node value
 * @return nodeInfoStruct related to this node
 */
nodeInfoStruct Graph::getNodeInfo(int node) { return this->_nodeInfo[node-1]; }


/**
 * @brief Get the Adjacent Nodes object.
 * 
 * @param node node value
 * @return list<int> representing a list of connected nodes
 */
list<int> Graph::getAdjacentNodes(int node) { return this->_adjacent[node-1]; }


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
void Graph::setNodeColor(int node, Color color) { this->_nodeInfo[node-1].color = color; }


/**
 * @brief Increments node's total in degree value.
 *
 * @param node node to be changed
 */
void Graph::incrementNodeInDegree(int node) { this->_nodeInfo[node-1].inDegree++; }


/**
 * @brief Changes node's distance.
 *
 * @param node node to be changed
 * @param dist new distance
 */
void Graph::setNodeDistance(int node, int dist) { this->_nodeInfo[node-1].dist = dist; }


/**
 * @brief Inserts a new edge from parent to child node.
 *
 * @param parent parent's node
 * @param child child's node
 */
void Graph::addEdge(int parent, int child) {

    /* Creates a connection between two nodes */
    this->_adjacent[parent-1].push_back(child);

    /* Increments child's in degrees */
    this->incrementNodeInDegree(child);

}


/**
 * @brief Performs an iterative DFS traversal of this graph starting from first node (1).
 *
 * @return list with nodes in topological order
 */
deque<int> Graph::dfs() {

    /* Holds nodes that we are visiting or are about to visit */
    deque<int> dfsAux;

    /* Holds nodes that have been already visited in topological order */
    deque<int> topological;

    /* Visits each node (domino piece) in our graph */
    for (int parent = 1; parent <= this->getNumberOfNodes(); parent++) {

        /* If it has not been yet visited, we put it inside our dfs aux */
        if (this->getNodeInfo(parent).color == Color::white)
            dfsAux.push_front(parent);

        /* We keep visiting node until all the nodes have turned black (fully visited) */
        while (!dfsAux.empty()) {

            /* Gets last node being put inside our auxiliary. It mimics what a recursion
             * would have done */
            int node = dfsAux.front();

            /* If we have already visited everything from this node, we put it in our topological
             * stack and go to next iteration */
            if (this->getNodeInfo(node).color == Color::black) {
                dfsAux.pop_front();
                topological.push_front(node);
                continue;
            }

            /* Since we are about to visit each child from this node, we set it as grey */
            this->setNodeColor(node, Color::grey);

            /* Puts every not yet visited child node inside aux */
            for (auto son : this->getAdjacentNodes(node))
                if(this->getNodeInfo(son).color == Color::white)
                    dfsAux.push_front(son);

            /* Since we have put all it's children inside the aux, it has finished */
            this->setNodeColor(node, Color::black);

        }

    }

    return topological;
}
