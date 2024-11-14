#include "graphs.h"

/**
 * breadth_first_traverse - traverses a graph using the breadth-first algorithm
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to call for each visited vertex
 * Return: maximum depth of the traversal, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
							  void (*action)(const vertex_t *v, size_t depth))
{
	size_t depth = 0, max_depth = 0, *lvl = NULL, front = 0, back = 0;
	char *visited = NULL;
	vertex_t **q = NULL, *vertex = NULL;
	edge_t *edge = NULL;

	if (!graph || !graph->vertices || !action)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(char));
	lvl = calloc(graph->nb_vertices, sizeof(size_t));
	q = malloc(sizeof(vertex_t *) * graph->nb_vertices);

	if (!visited || !lvl || !q)
	{
		free(visited); free(lvl); free(q);
		return (0);
	}
	vertex = graph->vertices; /* initialize traversal from the first vertex */
	visited[vertex->index] = 1; lvl[vertex->index] = 0; q[back++] = vertex;

	while (front < back) /* perform BFS traversal */
	{
		vertex = q[front++]; depth = lvl[vertex->index]; action(vertex, depth);

		if (depth > max_depth)
			max_depth = depth;
		for (edge = vertex->edges; edge; edge = edge->next) /* nq ajcnt vrtz */
		{
			if (!visited[edge->dest->index])
			{
				visited[edge->dest->index] = 1;
				lvl[edge->dest->index] = depth + 1;
				q[back++] = edge->dest;
			}
		}
	}
	free(visited); free(lvl); free(q);
	return (max_depth);
}
