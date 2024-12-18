#include "nary_trees.h"

/**
 * path_exists - checks if a path exists in an N-ary tree
 * @root: pointer to the root node of the tree
 * @path: NULL-terminated array of strings forming a path
 * Return: 1 if path exists, 0 otherwise.
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	nary_tree_t const *child;

	if (!path || !path[0])
		return (1); /* if path is empty, path trivially exists */
	if (!root)
		return (0); /* if root is NULL but path not empty, path doesnt exist */
	if (strcmp(root->content, path[0]) != 0)
		return (0); /* if current node's cntnt doesnt match currnt path lmnt */
	path++; /* move to next element in path */
	if (!path[0])
		return (1); /* if we've consumed all elements in path, success */
	child = root->children;
	while (child) /* try to find a child that matches the next path element */
	{ /* recursively check if path from this child downward exists */
		if (path_exists(child, path))
			return (1);
		child = child->next;
	} /* no child matched the next path element, so path doesnt exist */
	return (0);
}
