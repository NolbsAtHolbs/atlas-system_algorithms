#include "graphs.h"

size_t dfs_recur(const vertex_t *vertex,
				 void (*action)(const vertex_t *, size_t),
				 size_t depth, char *visited);

/**
 * depth_first_traverse - performs a depth-first traversal on a graph
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to be called for each visited vertex
 * Return: (biggest vertex depth), or (0) on failure
 */
size_t depth_first_traverse(const graph_t *graph,
							void (*action)(const vertex_t *v, size_t depth))
{
	size_t max_depth = 0;
	size_t depth = 0;

	if (graph == NULL || action == NULL || graph->vertices == NULL)
		return (0);
	size_t visited_size = graph->nb_vertices; /* mark all vrtcs as not vistd */
	char *visited = calloc(visited_size, sizeof(char));
	if (visited == NULL)
		return (0);
	/* start traversal from the first vertex in the vertices list */
	max_depth = dfs_recur(graph->vertices, action, depth, visited);
	free(visited);
	return (max_depth);
}

/**
 * dfs_recursive - recursive helper function for depth-first traversal
 * @vertex: current vertex being visited
 * @action: function to call for each visited vertex
 * @depth: current depth from the starting vertex
 * @visited: array to keep track of visited vertices
 * Return: maximum depth reached during traversal
 */
size_t dfs_recur(const vertex_t *vertex,
				 void (*action)(const vertex_t *, size_t),
				 size_t depth, char *visited)
{
	size_t max_depth = depth;
	edge_t *edge;

	if (visited[vertex->index])
		return (depth - 1);
	visited[vertex->index] = 1; /* mark the current vertex as visited */
	action(vertex, depth); /* call the action function on the current vertex */
	/* recursively visit adjacent vertices */
	for (edge = vertex->edges; edge != NULL; edge = edge->next)
	{
		size_t child_depth = dfs_recur(edge->dest, action, depth + 1, visited);
		if (child_depth > max_depth)
			max_depth = child_depth;
	}
	return (max_depth);
}
