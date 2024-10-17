//315112870 Mor Hanania
//206945107 Yuval Arbel
#ifndef EX2_CODE_BFS_H
#define EX2_CODE_BFS_H

#include "SyncGraph/graph.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Performs the Breadth-First Search (BFS) algorithm on the given graph to compute the shortest path matrix.
 * This function is compatible with C code.
 * @param graph The graph on which to perform BFS.
 * @param m A pointer to a 2D array (matrix) where the shortest path distances will be stored.
 *          The matrix should be pre-allocated with dimensions equal to the number of vertices in the graph.
 *          Each cell in the matrix (i, j) represents the shortest path distance from vertex i to vertex j.
 *          If there is no path from i to j, the distance is marked as -1 (infinity).
 */
void bfs(Graph *graph, int **m);

#ifdef __cplusplus
}
#endif

#endif //EX2_CODE_BFS_H
