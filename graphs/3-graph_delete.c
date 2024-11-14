#include "graphs.h"

/**
 * graph_delete - completely deletes a graph
 * @graph: pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
	vertex_t *vertex, *tmp_vertex;
	edge_t *edge, *tmp_edge;

	if (graph == NULL)
		return;
	vertex = graph->vertices; /* iterate through all vertices */
	while (vertex != NULL)
	{
		edge = vertex->edges; /* free all edges of the vertex */
		while (edge != NULL)
		{
			tmp_edge = edge->next; /* temp ptr to store next edge */
			free(edge);
			edge = tmp_edge;
		}
		if (vertex->content) /* free the content of the vertex */
			free(vertex->content);
		tmp_vertex = vertex->next; /* move to the next vertex */
		free(vertex);
		vertex = tmp_vertex;
	}
	free(graph);
}
