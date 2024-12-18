#include "nary_trees.h"

/**
 * traverse_helper - recursive helper function that carries the current depth
 * @node: current node being visited
 * @action: function pointer to action to perform on node
 * @current_depth: current depth of this node
 * Return: maximum depth found in this subtree
 */
static size_t traverse_helper(nary_tree_t const *node,
			      void (*action)(nary_tree_t const *, size_t),
			      size_t current_depth)
{
	size_t max_child_depth = 0, child_depth;
	nary_tree_t const *child;

	action(node, current_depth); /* call action on crrnt node w/ crrnt depth */
	for (child = node->children; child; child = child->next)
	{ /* traverse each child, increase depth by 1 for children */
		child_depth = traverse_helper(child, action, current_depth + 1);
		if (child_depth > max_child_depth)
			max_child_depth = child_depth;
	}
	if (max_child_depth > 0)
		return (max_child_depth);
	else
		return (current_depth);
}

/**
 * nary_tree_traverse - goes through an N-ary tree, node by node
 * @root: pointer to the root node of the tree to traverse
 * @action: pointer to a function to execute for each node visited
 */
size_t nary_tree_traverse(nary_tree_t const *root,
			  void (*action)(nary_tree_t const *node, size_t depth))
{
	if (!root)
		return (0); /* no root, no depth */
	return traverse_helper(root, action, 0);
} /* use the helper function starting at depth = 0 */
