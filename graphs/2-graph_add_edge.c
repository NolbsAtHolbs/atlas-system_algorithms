#include "graphs.h"

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
	edge_t *new_edge_src;

	if (graph == NULL || src == NULL || dest == NULL)
		return (0);
	/* search for src and dest vertices */
	for (vertex = graph->vertices; vertex != NULL; vertex = vertex->next)
	{
		if (strcmp(vertex->content, src) == 0)
			src_vertex = vertex;
		if (strcmp(vertex->content, dest) == 0)
			dest_vertex = vertex;
		if (src_vertex != NULL && dest_vertex != NULL)
			break;
	}
	if (src_vertex == NULL || dest_vertex == NULL)
		return (0);
	new_edge_src = malloc(sizeof(edge_t)); /* cre8 edg frm src_vtx 2 dst_vtx */

	if (new_edge_src == NULL)
		return (0);
	new_edge_src->dest = dest_vertex; new_edge_src->next = src_vertex->edges;
	src_vertex->edges = new_edge_src; src_vertex->nb_edges++;

	if (type == BIDIRECTIONAL)
	{
		edge_t *new_edg_dst = malloc(sizeof(edge_t));

		if (new_edg_dst == NULL)
		{
			src_vertex->edges = new_edge_src->next; /* undo previous edge */
			src_vertex->nb_edges--;
			free(new_edge_src);
			return (0);
		}
		new_edg_dst->dest = src_vertex; new_edg_dst->next = dest_vertex->edges;
		dest_vertex->edges = new_edg_dst; dest_vertex->nb_edges++;
	}
	return (1);
}
