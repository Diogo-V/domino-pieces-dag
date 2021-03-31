#include <iostream>
#include <vector>
#include <deque>


#define NEGATIVE_INFINITY -100
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
 * @param dist holds distance to another Source
 */
typedef struct nodeInfoStruct {
    Color color;
    int inDegree;
    int dist;
    nodeInfoStruct() {
        color = Color::white;
        inDegree = 0;
        dist = 1;
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
        vector<vector<int>> _adjacent;

        /**
         * @brief Holds number of vertices inside this graph.
         */
        int _numberOfNodes;

        /**
         * @brief Holds number of times we have to push a domino piece to make all the pieces fall.
         */
        int _interventions;

    public:

        /**
         * @brief Graph constructor.
         *
         * @param nodes number of nodes inside graph
         */
        explicit Graph(int nodes) {

            /* Populates info vector with all the possible nodes */
            nodeInfoStruct info;
            this->_nodeInfo.resize(nodes, info);

            /* Creates and allocates space for all the nodes' connections */
            this->_adjacent.resize(nodes);

            /* Saves number of nodes */
            this->_numberOfNodes = nodes;

            /* Initially the number of interventions is going to be the same as the number of nodes
             * and each time we add a new edge that increments a node's in degree, we decrease this
             * value */
            this->_interventions = nodes;

        };

        /**
         * @brief Get the Node Info object.
         *
         * @param node node value
         * @return nodeInfoStruct related to this node
         */
        nodeInfoStruct getNodeInfo(int node) { return this->_nodeInfo[node-1]; };

        /**
         * @brief Get the Adjacent Nodes object.
         *
         * @param node node value
         * @return vector<int> representing a list of connected nodes
         */
        vector<int> getAdjacentNodes(int node) { return this->_adjacent[node-1]; };

        /**
         * @brief Get the Number of Nodes object.
         *
         * @return number of nodes
         */
        int getNumberOfNodes() const { return this->_numberOfNodes; };

        /**
         * @brief Get the Number of Interventions object.
         *
         * @return number of interventions
         */
        int getNumberOfInterventions() const { return this->_interventions; };

        /**
         * @brief Changes node's current color.
         *
         * @param node node to be changed
         * @param color new color
         */
        void setNodeColor(int node, Color color) { this->_nodeInfo[node-1].color = color; };

        /**
         * @brief Increments node's total in degree value.
         *
         * @param node node to be changed
         */
        void incrementNodeInDegree(int node) { this->_nodeInfo[node-1].inDegree++; };

        /**
         * @brief Increments node's total in degree value.
         */
        void decrementNumberInterventions() { this->_interventions--; };

        /**
         * @brief Changes node's distance.
         *
         * @param node node to be changed
         * @param dist new distance
         */
        void setNodeDistance(int node, int dist) { this->_nodeInfo[node-1].dist = dist; };

        /**
         * @brief Inserts a new edge from parent to child node.
         *
         * @param parent parent's node
         * @param child child's node
         */
        void addEdge(int parent, int child) {

            /* Creates a connection between two nodes */
            this->_adjacent[parent-1].push_back(child);

            /* Increments child's in degrees and decrements number of interventions if it is the
             * first time this node is referenced. Also changes it's distance to infinity */
            if (this->getNodeInfo(child).inDegree == 0) {
                this->decrementNumberInterventions();
                this->setNodeDistance(child, NEGATIVE_INFINITY);
            }
            this->incrementNodeInDegree(child);

        }

        /**
         * @brief Performs an iterative DFS traversal of this graph starting from first node (1).
         *
         * @return deque with nodes in topological order
         */
        deque<int> dfs() {

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
                    for (int son : this->getAdjacentNodes(node))
                        if(this->getNodeInfo(son).color == Color::white)
                            dfsAux.push_front(son);

                    /* Since we have put all it's children inside the aux, it has finished */
                    this->setNodeColor(node, Color::black);

                }

            }

            return topological;
        }

};


/**
 * @brief Creates and populates the graph that is going to represent all the pieces' placement.
 *
 * @return newly created graph
 */
Graph initGraph() {

    /* Receive number of nodes and vertices from cin */
    int nNodes = 0, nEdges = 0;

    /* Hold parent and child node numbers while populating */
    int parent = 0, child = 0;

    /* Reads number of nodes and edges from cin */
    scanf("%d %d", &nNodes, &nEdges);

    /* Creates graph */
    Graph graph(nNodes);

    /* Populates graph with all the edges from cin */
    for (int i = 0; i < nEdges; i++) {
        scanf("%d %d", &parent, &child);
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

    /* Holds the number of nodes traversed in the longest sequence of dominoes */
    int sequence = 1;

    /* We traverse all the nodes in our topological stack and traverse them one by one. While doing
     * this, we traverse their children and change their distance. This will count the number of
     * edges between them and their parents */
    while ( ! topological->empty()) {

        /* Gets node from stack */
        int node = topological->front(); topological->pop_front();

        /* Traverses children sets their distance */
        if (graph->getNodeInfo(node).dist != NEGATIVE_INFINITY) {

            int dist = graph->getNodeInfo(node).dist + 1;

            for (int child: graph->getAdjacentNodes(node)) {

                if (graph->getNodeInfo(child).dist < dist) {

                    graph->setNodeDistance(child, dist);

                    /* Finds and holds longest distance. Is done here as to avoid doing another loop
                     * to find the highest distance */
                    if (dist > sequence) sequence = dist;

                }

            }

        }

    }

    /* Outputs final result */
    cout << graph->getNumberOfInterventions() << " " << sequence << endl;

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
