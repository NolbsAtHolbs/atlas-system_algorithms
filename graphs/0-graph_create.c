#include "graphs.h"

/**
 * graph_create - mallocs to store a graph_t structure, & inits its content
 * Return: pointer to allocated graph_t structure, or NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *graph;

	graph = malloc(sizeof(graph_t));
	if (graph == NULL)
		return (NULL);
	graph->nb_vertices = 0;
	graph->vertices = NULL;
	return (graph);
}
