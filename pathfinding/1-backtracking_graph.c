#include "pathfinding.h"

int backtrack(vertex_t const *current, vertex_t const *target,
			  queue_t *path, queue_t *visited);

/**
 * backtracking_graph - searches for a path from start to target in a graph
 * @graph: pointer to the graph to traverse
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * Return: queue in which each node is a char * corresponding to a vertex,
 *         forming a path from start to target, or NULL if no path is found
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
							vertex_t const *target)
{
	queue_t *path = NULL;
	queue_t *visited = NULL;

	if (!graph || !start || !target)
		return (NULL);
	path = queue_create();
	if (!path)
		return (NULL);
	visited = queue_create();
	if (!visited)
	{
		queue_delete(path);
		return (NULL);
	}
	if (backtrack(start, target, path, visited))
	{
		queue_delete(visited);
		return (path);
	}
	else
	{
		queue_delete(visited);
		queue_delete(path);
		return (NULL);
	}
}

/**
 * backtrack - recursive helper function to find path from current to target
 * @current: pointer to the current vertex
 * @target: pointer to the target vertex
 * @path: queue to store the path
 * @visited: queue to keep track of visited vertices
 *
 * Return: 1 if path is found, 0 otherwise
 */
int backtrack(vertex_t const *current, vertex_t const *target,
			  queue_t *path, queue_t *visited)
{
	edge_t *edge;
	char *vertex_name;
	queue_node_t *node;

	for (node = visited->front; node; node = node->next)
	{ /* check if current vertex is already visited */
		if (node->ptr == current)
			return (0);
	} /* mark current vertex as visited */
	if (!queue_push_back(visited, (void *)current))
		return (0);
	printf("Checking %s\n", current->content);
	if (current == target) /* check if current vertex is the target */
	{
		vertex_name = strdup(current->content);
		if (!vertex_name)
			return (0);
		if (!queue_push_front(path, vertex_name))
		{
			free(vertex_name);
			return (0);
		}
		return (1);
	} /* explore adjacent vertices */
	for (edge = current->edges; edge; edge = edge->next)
	{
		if (backtrack(edge->dest, target, path, visited))
		{
			vertex_name = strdup(current->content);
			if (!vertex_name)
				return (0);
			if (!queue_push_front(path, vertex_name))
			{
				free(vertex_name);
				return (0);
			}
			return (1);
		}
	}
	return (0);
}
