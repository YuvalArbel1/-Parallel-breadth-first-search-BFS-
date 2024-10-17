#include "bfs.h"
#include "ThreadPool.h"
#include <mutex>
#include <vector>
#include <queue>


/**
 * Performs BFS from a given start vertex and updates the shortest path matrix `m`.
 * @param graph The graph to traverse.
 * @param startVertex The starting vertex for BFS.
 * @param m The matrix to store the shortest paths.
 * @param m_mtx Mutex for synchronizing access to the matrix.
 */
void bfsFromVertex(Graph *graph, int startVertex, int **m, std::mutex &m_mtx) {
    // Keeps track of visited vertices to avoid revisiting them
    std::vector<bool> visited(graph->numVertices, false);

    // Queue to manage the BFS traversal. Store pairs of vertex and its depth.
    std::queue<std::pair<int, int>> q;

    // Mark the starting vertex as visited and enqueue it with depth 0
    visited[startVertex] = true;
    q.push({startVertex, 0});

    // Process the queue until it's empty
    while (!q.empty()) {
        // Extract the vertex and its depth from the queue
        int v = q.front().first;
        int depth = q.front().second;
        q.pop();

        // Lock the mutex before accessing the shared matrix
        std::lock_guard<std::mutex> lock(m_mtx);
        // Update the distance of the vertex from the start vertex in the matrix
        m[startVertex][v] = depth;

        // Explore all adjacent vertices
        for (node *adj = graph->adjacencyLists[v]; adj != nullptr; adj = adj->next) {
            int adjVertex = adj->v;
            // If the adjacent vertex has not been visited, mark it visited and enqueue it
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                // Enqueue the adjacent vertex with a depth incremented by 1
                q.push({adjVertex, depth + 1});

                // Note: As we enqueue each adjacent vertex, we increase the depth by 1.
                // This ensures that vertices enqueued consecutively have a depth difference of at most 1.
                // This is crucial for maintaining the breadth-first nature of the traversal.
            }
        }
    }
}

/**
 * Initializes the shortest path matrix and manages the parallel execution of BFS tasks.
 * @param graph The graph on which BFS is performed.
 * @param m The matrix to be updated with shortest path distances.
 */
void bfs(Graph *graph, int **m) {
    // Number of vertices in the graph
    const unsigned int numVertices = graph->numVertices;
    // Create a thread pool with a number of threads equal to the hardware concurrency
    ThreadPool pool(std::thread::hardware_concurrency());
    // Mutex for synchronizing access to the shortest path matrix
    std::mutex m_mtx;

    // Initialize the shortest path matrix with -1 (infinity)
    for (unsigned int i = 0; i < numVertices; i++) {
        // Set all distances to -1
        std::fill(m[i], m[i] + numVertices, -1);
        // Distance to self is 0
        m[i][i] = 0;
    }

    // Enqueue BFS tasks for each vertex
    for (int i = 0; i < numVertices; i++) {
        pool.enqueue([graph, i, m, &m_mtx] {
            // Perform BFS from each vertex
            bfsFromVertex(graph, i, m, m_mtx);
        });
    }

    // The ThreadPool destructor will automatically wait for all tasks to complete
}
