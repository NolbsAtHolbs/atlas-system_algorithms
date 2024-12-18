#include "nary_trees.h"

/**
 * nary_height_diameter - computes subtree height & updates diam
 * @root: pointer to current node
 * @diameter: pointer to current maximum diameter found
 * Return: diameter of the tree pointed to by root
 */
static size_t calc_nary_height_and_update_diameter(const nary_tree_t *root,
						   size_t *diameter)
{
	size_t max_h1 = 0, max_h2 = 0;
	size_t child_height;
	const nary_tree_t *child;

	if (!root)
		return (0);
	child = root->children;
	while (child)
	{
		child_height = nary_height_diameter(child, diameter);
		if (child_height > max_h1)
		{ /* update largest heights */
			max_h2 = max_h1;
			max_h1 = child_height;
		}
		else if (child_height > max_h2)
			max_h2 = child_height;
		child = child->next;
	} /* update diameter if sum of two largest heights is bigger */
	if (max_h1 + max_h2 > *diameter)
		*diameter = max_h1 + max_h2;
	if (!root->children)
		return (0); /* no children, no height */
	return (max_h1 + 1); /* else height = top child's height + 1 edge */
}

/**
 * nary_tree_diameter - computes the diameter of an N-ary tree
 * @root: pointer to root of the tree
 * Returns: 0 if tree is empty, diameter if not empty (diameter in edges)
 */
size_t nary_tree_diameter(const nary_tree_t *root)
{
	size_t diameter = 0;

	if (!root)
		return 0;
	nary_height_diameter(root, &diameter);
	if (diameter == 0)
		return (0);
	return (diameter + 1);
} /* if root exists, add 1 to diameter to count edges properly */
