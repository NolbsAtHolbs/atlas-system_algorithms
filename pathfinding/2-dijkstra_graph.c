#include "pathfinding.h"

int dijkstra_algorithm(graph_t *graph, vertex_t const *start,
					   vertex_t const *target, int *visited,
					   int *dist, vertex_t **prev);
queue_t *build_path(vertex_t const *start, vertex_t const *target,
					vertex_t **prev);

/**
 * dijkstra_graph - finds the shortest path from start to target using Dijkstra's algorithm
 * @graph: pointer to the graph
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * Return: queue containing the path from start to target, or NULL if no path found
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
						vertex_t const *target)
{
	queue_t *path = NULL;
	int *visited = NULL, *dist = NULL;
	vertex_t **prev = NULL, *vertex = NULL;
	size_t i;
	if (!graph || !start || !target)
		return (NULL);
	visited = calloc(graph->nb_vertices, sizeof(int));
	dist = malloc(sizeof(int) * graph->nb_vertices);
	prev = calloc(graph->nb_vertices, sizeof(vertex_t *));
	if (!visited || !dist || !prev)
		return (free(visited), free(dist), free(prev), NULL);
	for (i = 0; i < graph->nb_vertices; i++)
		dist[i] = INT_MAX;
	dist[start->index] = 0;
	if (!dijkstra_algorithm(graph, start, target, visited, dist, prev))
	{
		free(visited), free(dist), free(prev);
		return (NULL);
	}
	path = build_path(start, target, prev);
	free(visited), free(dist), free(prev);
	return (path);
}

/**
 * dijkstra_algorithm - implements Dijkstra's algorithm
 * @graph: pointer to the graph
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * @visited: array to keep track of visited vertices
 * @dist: array of distances from start to each vertex
 * @prev: array of predecessors for each vertex
 * Return: 1 on success, 0 on failure
 */
int dijkstra_algorithm(graph_t *graph, vertex_t const *start,
					   vertex_t const *target, int *visited,
					   int *dist, vertex_t **prev)
{
	vertex_t *vertex = NULL, *min_vertex = NULL;
	edge_t *edge = NULL;
	int min_dist, alt;

	while (1)
	{
		min_dist = INT_MAX;
		min_vertex = NULL;
		for (vertex = graph->vertices; vertex; vertex = vertex->next)
		{ /* find the unvisited vertex with the smallest distance */
			if (!visited[vertex->index] && dist[vertex->index] < min_dist)
			{
				min_dist = dist[vertex->index];
				min_vertex = vertex;
			}
		}
		if (!min_vertex)
			break;
		visited[min_vertex->index] = 1;
		printf("Checking %s, distance from %s is %d\n",
			   min_vertex->content, start->content, dist[min_vertex->index]);
		if (min_vertex == target)
			return (1); /* update distances to adjacent vertices */
		for (edge = min_vertex->edges; edge; edge = edge->next)
		{
			if (!visited[edge->dest->index])
			{
				alt = dist[min_vertex->index] + edge->weight;
				if (alt < dist[edge->dest->index])
				{
					dist[edge->dest->index] = alt;
					prev[edge->dest->index] = min_vertex;
				}
			}
		}
	}
	return (dist[target->index] != INT_MAX);
}

/**
 * build_path - builds the path from start to target using predecessors
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 * @prev: array of predecessors for each vertex
 * Return: queue containing the path, or NULL on failure
 */
queue_t *build_path(vertex_t const *start, vertex_t const *target,
					vertex_t **prev)
{
	queue_t *path = queue_create();
	vertex_t *vertex = (vertex_t *)target;
	char *name;

	if (!path)
		return (NULL);
	while (vertex)
	{
		name = strdup(vertex->content);
		if (!name)
		{
			queue_delete(path);
			return (NULL);
		}
		if (!queue_push_front(path, name))
		{
			free(name);
			queue_delete(path);
			return (NULL);
		}
		if (vertex == start)
			break;
		vertex = prev[vertex->index];
	}
	return (path);
}
