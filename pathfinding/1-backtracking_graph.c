#include "pathfinding.h"

int backtrack(vertex_t const *current, vertex_t const *target,
			  queue_t *path, int *visited);

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
    int *visited = NULL;

    if (!graph || !start || !target)
        return (NULL);
    path = queue_create();
    if (!path)
        return (NULL);
    /* allocate an array to keep track of visited vertices */
    visited = calloc(graph->nb_vertices, sizeof(int));
    if (!visited)
    {
        queue_delete(path);
        return (NULL);
    }
    if (backtrack(start, target, path, visited))
    {
        free(visited);
        return (path);
    }
    else
    {
        free(visited);
        queue_delete(path);
        return (NULL);
    }
}

/**
 * backtrack - recursive helper function to find path from current to target
 * @current: pointer to the current vertex
 * @target: pointer to the target vertex
 * @path: queue to store the path
 * @visited: array to keep track of visited vertices by index
 * Return: 1 if path is found, 0 otherwise
 */
int backtrack(vertex_t const *current, vertex_t const *target,
              queue_t *path, int *visited)
{
    edge_t *edge;
    char *vertex_name;

    printf("Checking %s\n", current->content);
    if (visited[current->index])
        return (0);
    visited[current->index] = 1;
    if (current == target)
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
