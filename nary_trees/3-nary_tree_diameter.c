#include "nary_trees.h"

/**
 * nary_height - computes the height of an N-ary tree's subtree
 * @root: pointer to the subtree root node
 * Return: height of the subtree.
 */
static size_t nary_height(const nary_tree_t *root)
{
	size_t max_height = 0;
	size_t child_height;
	const nary_tree_t *child;

	if (!root)
		return (0);
	child = root->children;
	while (child)
	{ /* find the tallest child's height */
		child_height = nary_height(child);
		if (child_height > max_height)
			max_height = child_height;
		child = child->next;
	} /* height is tallest child's height + 1 if any child exists, else 0 */
	return (max_height + 1);
}

/**
 * nary_tree_diameter - computes the diameter of an N-ary tree
 * @root: pointer to the root of the tree
 * Return: diameter of the tree, or 0 if empty.
 */
size_t nary_tree_diameter(const nary_tree_t *root)
{
	size_t top_height1 = 0, top_height2 = 0;
	size_t child_height, current_diameter = 0;
	size_t node_diameter;
	const nary_tree_t *child;

	if (!root)
		return (0);
	child = root->children;
	while (child)
	{ /* compute top 2 heights of children and update diameter from subtrees */
		child_height = nary_height(child); 
		if (child_height > top_height1)
		{ /* update top two heights */
			top_height2 = top_height1;
			top_height1 = child_height;
		}
		else if (child_height > top_height2)
			top_height2 = child_height;
		node_diameter = nary_tree_diameter(child); /* compute subtree's diameter */
		if (node_diameter > current_diameter)
			current_diameter = node_diameter; /* update current_diameter if larger */
		child = child->next;
	}
	size_t candidate = top_height1 + top_height2 + 1;
	/* candidate diameter at this node = sum of top two heights + 1 edge */
	if (candidate > current_diameter)
		current_diameter = candidate;
	return (current_diameter);
}
