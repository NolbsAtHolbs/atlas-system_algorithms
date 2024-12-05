#include "pathfinding.h"

int backtrack(char **map, int rows, int cols, int x, int y,
			  point_t const *target, queue_t *path, int *visited);

/**
 * backtracking_array - searches for a path from start to target in a 2D array
 * @map: pointer to a read-only two-dimensional array
 * @rows: number of rows in map
 * @cols: number of columns in map
 * @start: pointer to the starting point
 * @target: pointer to the target point
 * Return: queue where each node is a point in the path from start to target,
 *         or NULL if no path is found
 */
queue_t *backtracking_array(char **map, int rows, int cols,
							point_t const *start, point_t const *target)
{
	queue_t *path;
	int *visited;

	if (!map || !start || !target || rows <= 0 || cols <= 0)
		return (NULL);
	path = queue_create();
	if (!path)
		return (NULL);
	visited = calloc(rows * cols, sizeof(int));
	if (!visited)
	{
		queue_delete(path);
		return (NULL);
	}
	if (!backtrack(map, rows, cols, start->x, start->y, target, path, visited))
	{
		queue_delete(path);
		free(visited);
		return (NULL);
	}
	free(visited);
	return (path);
}

/**
 * backtrack - recursively searches for a path from current position to target
 * @map: pointer to a read-only two-dimensional array
 * @rows: number of rows in map
 * @cols: number of columns in map
 * @x: current x coordinate
 * @y: current y coordinate
 * @target: pointer to the target point
 * @path: queue to store the path
 * @visited: array to keep track of visited cells
 *
 * Return: 1 if path is found, 0 otherwise
 */
int backtrack(char **map, int rows, int cols, int x, int y,
			  point_t const *target, queue_t *path, int *visited)
{
	point_t *point;

	if (x < 0 || x >= cols || y < 0 || y >= rows ||
	    map[y][x] == '1' || visited[y * cols + x])
		return (0);
	printf("Checking coordinates [%d, %d]\n", x, y);
	visited[y * cols + x] = 1;
	if (x == target->x && y == target->y)
	{
		point = malloc(sizeof(point_t));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		if (!queue_push_front(path, point))
		{
			free(point);
			return (0);
		}
		return (1);
	}
	if (backtrack(map, rows, cols, x + 1, y, target, path, visited) ||
		backtrack(map, rows, cols, x, y + 1, target, path, visited) ||
		backtrack(map, rows, cols, x - 1, y, target, path, visited) ||
		backtrack(map, rows, cols, x, y - 1, target, path, visited))
	{
		point = malloc(sizeof(point_t));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		if (!queue_push_front(path, point))
		{
			free(point);
			return (0);
		}
		return (1);
	}
	return (0);
}
