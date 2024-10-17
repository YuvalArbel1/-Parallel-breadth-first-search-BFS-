#ifndef EX2_CODE_GRAPH_H
#define EX2_CODE_GRAPH_H


#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration of the Graph structure for use in C functions
typedef struct Graph Graph;

/**
 * Creates a graph with a specified number of vertices (C-compatible function).
 * @param vertices The number of vertices in the graph.
 * @return Pointer to the newly created graph.
 */
Graph *createGraph(int vertices);

/**
 * Adds an edge between two vertices in a graph (C-compatible function).
 * @param graph The graph to which the edge is added.
 * @param source The source vertex of the edge.
 * @param destination The destination vertex of the edge.
 */
void addEdge(Graph *graph, int source, int destination);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <mutex>

// Node structure representing a vertex and a linked list to store adjacency lists
struct node {
    int v;
    node *next;
};


// Graph class representing an undirected graph with adjacency list representation
class Graph {
public:
    // Number of vertices in the graph
    unsigned int numVertices;
    // Array of pointers to node, representing adjacency lists
    node **adjacencyLists;
    // Array to track the number of visits to each vertex (used in BFS)
    int *numVisits;
    // Array of mutexes, one for each vertex
    std::mutex *num_visits_mutexes;

    /**
     * Constructor for Graph class. Initializes a graph with a given number of vertices.
     * @param vertices The number of vertices in the graph.
     */
    explicit Graph(int vertices);

    /**
     * Destructor for Graph class. Frees the allocated memory for the graph.
     */
    ~Graph();

    /**
     * Adds an edge between two vertices in the graph.
     * @param source The source vertex for the edge.
     * @param destination The destination vertex for the edge.
     */
    void addEdge(int source, int destination);

    /**
     * Creates a new node with the given vertex value (used in adjacency list).
     * @param v The vertex value for the new node.
     * @return Pointer to the newly created node.
     */
    node *createNode(int v);
};

#endif
#endif //EX2_CODE_GRAPH_H
