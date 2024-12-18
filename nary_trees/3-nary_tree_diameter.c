#include "nary_trees.h"

/**
 * nary_height_diameter - computes subtree height & updates diam
 * @root: pointer to current node
 * @diameter: pointer to current maximum diameter found
 * Return: node height
 */
static size_t nary_height_diameter(nary_tree_t const *root, size_t *diameter)
{
	size_t max_h1 = 0, max_h2 = 0; /* top two child heights */
	size_t child_height;
	nary_tree_t const *child;

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
	} /* update diameter if needed */
	if (max_h1 + max_h2 > *diameter)
		*diameter = max_h1 + max_h2;
	if (!root->children)
		return (0); /* no child, no height */
	return (max_h1 + 1); /* otherwise, height = tallest child's height + 1 */
}

/**
 * nary_tree_diameter - computes diameter of an N-ary tree
 * @root: pointer to root node
 * Return: diameter of the tree, or 0 if empty.
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;

	nary_height_diameter(root, &diameter);
	return (diameter + 1);
} /* if there's at least one node, return diameter + 1 */
