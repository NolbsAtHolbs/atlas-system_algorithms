
#include "graphs.h"

/**
 * breadth_first_traverse - traverses a graph using the breadth-first algorithm
 * @graph: pointer to the graph to traverse
 * @action: pointer to a function to call for each visited vertex
 *
 * Return: maximum depth of the traversal, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
			      void (*action)(const vertex_t *v, size_t depth))
{
	size_t depth = 0, max_depth = 0;
	size_t *level = NULL;
	char *visited = NULL;
	vertex_t **queue = NULL;
	size_t front = 0, back = 0;
	vertex_t *vertex = NULL;
	edge_t *edge = NULL;

	if (!graph || !graph->vertices || !action)
		return (0);

	/* Allocate memory for visited array, level array, and queue */
	visited = calloc(graph->nb_vertices, sizeof(char));
	level = calloc(graph->nb_vertices, sizeof(size_t));
	queue = malloc(sizeof(vertex_t *) * graph->nb_vertices);

	if (!visited || !level || !queue)
	{
		free(visited);
		free(level);
		free(queue);
		return (0);
	}

	/* Initialize the traversal from the first vertex */
	vertex = graph->vertices;
	visited[vertex->index] = 1;
	level[vertex->index] = 0;
	queue[back++] = vertex;

	/* Perform BFS traversal */
	while (front < back)
	{
		vertex = queue[front++];
		depth = level[vertex->index];
		action(vertex, depth);

		if (depth > max_depth)
			max_depth = depth;

		/* Enqueue adjacent vertices */
		for (edge = vertex->edges; edge; edge = edge->next)
		{
			if (!visited[edge->dest->index])
			{
				visited[edge->dest->index] = 1;
				level[edge->dest->index] = depth + 1;
				queue[back++] = edge->dest;
			}
		}
	}

	/* Free allocated memory */
	free(visited);
	free(level);
	free(queue);

	return (max_depth);
}
