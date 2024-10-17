#include "graph.h"

#ifdef __cplusplus

/**
 * Creates a new node with the given vertex value.
 * @param v The vertex value for the new node.
 * @return Pointer to the newly created node.
 */
node *Graph::createNode(int v) {
    // Allocate memory for a new node
    node *newNode = new node;
    // Set the vertex value
    newNode->v = v;
    // Initialize the next pointer to null
    newNode->next = nullptr;

    return newNode;
}


/**
 * Adds an edge between two vertices in the graph.
 * @param source The source vertex for the edge.
 * @param destination The destination vertex for the edge.
 */
void Graph::addEdge(int source, int destination) {
    // Create a new node for the destination and add it to the adjacency list of the source
    node *newNode = createNode(destination);
    newNode->next = adjacencyLists[source];
    adjacencyLists[source] = newNode;

    // Since it's an undirected graph, add an edge in the opposite direction as well
    newNode = createNode(source);
    newNode->next = adjacencyLists[destination];
    adjacencyLists[destination] = newNode;
}

/**
 * Constructor for the Graph class. Initializes a graph with a given number of vertices.
 * @param vertices The number of vertices in the graph.
 */
Graph::Graph(int vertices) {
    // Set the number of vertices
    numVertices = vertices;
    // Allocate memory for adjacency lists
    adjacencyLists = new node *[vertices];
    // Allocate memory for visit counts
    numVisits = new int[vertices];
    // Allocate memory for mutexes
    num_visits_mutexes = new std::mutex[vertices];

    for (int i = 0; i < vertices; i++) {
        // Initialize adjacency lists to null
        adjacencyLists[i] = nullptr;
        // Initialize visit counts to 0
        numVisits[i] = 0;
    }
}

/**
 * Destructor for the Graph class. Frees allocated memory.
 */
Graph::~Graph() {
    // Free each adjacency list
    for (int i = 0; i < numVertices; i++) {
        delete[] adjacencyLists[i];
    }
    // Free the array of adjacency lists
    delete[] adjacencyLists;
    // Free the array of visit counts
    delete[] numVisits;
    // Free the array of mutexes
    delete[] num_visits_mutexes;
}

extern "C" {
// C-compatible functions to create a graph and add edges

/**
 * Creates a graph with a specified number of vertices.
 * @param vertices The number of vertices in the graph.
 * @return Pointer to the newly created graph.
 */
Graph *createGraph(int vertices) {
    return new Graph(vertices);
}

/**
 * Adds an edge between two vertices in a graph.
 * @param graph The graph to which the edge is added.
 * @param source The source vertex of the edge.
 * @param destination The destination vertex of the edge.
*/
void addEdge(Graph *graph, int source, int destination) {
    graph->addEdge(source, destination);
}
}
#endif
