#include "graphs.h"

int vrtx_add_edge(vertex_t *src, vertex_t *dest);

/**
 * vrtx_add_edge - adds an edge from a source vertex to a destination vertex
 * @src: pointer to source vertex
 * @dest: pointer to destination vertex
 * Return: 1 on success, else 0
 */
int vrtx_add_edge(vertex_t *src, vertex_t *dest)
{
	edge_t *new_edge, *edge;

	new_edge = malloc(sizeof(edge_t));
	if (new_edge == NULL)
		return (0);
	new_edge->dest = dest;
	new_edge->next = NULL;
	if (src->edges == NULL)
		src->edges = new_edge;
	else
	{
		for (edge = src->edges; edge->next; edge = edge->next)
			;
		edge->next = new_edge;
	}
	src->nb_edges++;
	return (1);
}

/**
 * graph_add_edge - adds an edge between two vertices to an existing graph
 * @graph: pointer to the graph to add the edge to
 * @src: string identifying the vertex to make the connection from
 * @dest: string identifying the vertex to connect to
 * @type: type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 * Return: 1 on success, else 0
 */
int graph_add_edge(graph_t *graph, const char *src,
		   const char *dest, edge_type_t type)
{
	vertex_t *src_vertex = NULL, *dest_vertex = NULL, *vertex;

	if (!graph || !src || !dest)
		return (0);
	for (vertex = graph->vertices; vertex; vertex = vertex->next)
	{
		if (strcmp(vertex->content, src) == 0)
			src_vertex = vertex;
		if (strcmp(vertex->content, dest) == 0)
			dest_vertex = vertex;
	}
	if (!src_vertex || !dest_vertex || !vrtx_add_edge(src_vertex, dest_vertex))
		return (0);
	if (type == BIDIRECTIONAL)
		return (vrtx_add_edge(dest_vertex, src_vertex));
	return (1);
}
