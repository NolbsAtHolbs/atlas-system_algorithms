#include "graphs.h"

/**
 * graph_add_vertex - adds a vertex to an existing graph
 * @graph: pointer to the graph to add the vertex to
 * @str: string to store in the new vertex
 *
 * return: pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex, *temp;

	if (graph == NULL || str == NULL)
		return (NULL);
	temp = graph->vertices; /* check if a vrtx w/ same content already xists */
	while (temp)
	{
		if (strcmp(temp->content, str) == 0)
			return (NULL);
		temp = temp->next;
	}
	new_vertex = malloc(sizeof(vertex_t)); /* malloc for the new vertex */
	if (new_vertex == NULL)
		return (NULL);
	new_vertex->content = strdup(str); /* initialize the new vertex */
	if (new_vertex->content == NULL)
	{
		free(new_vertex);
		return (NULL);
	}
	new_vertex->index = graph->nb_vertices;
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (graph->vertices == NULL) /* add new vertex to end of adjacency list */
		graph->vertices = new_vertex;
	else
	{
		temp = graph->vertices;
		while (temp->next)
			temp = temp->next;
		temp->next = new_vertex;
	}
	graph->nb_vertices++; /* update num of vertices in the graph */
	return (new_vertex);
}
