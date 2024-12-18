#include "nary_trees.h"

/**
 * nary_tree_delete - deallocates an entire N-ary tree
 * @tree: pointer to the root node of the tree
 */
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *child, *next_child;

	if (!tree)
		return; /* if tree is NULL, nothing to do */
	for (child = tree->children; child; child = next_child)
	{ /* loop through each child of the current node */
		next_child = child->next; /* store child's nxt ptr b4 deleting child */
		nary_tree_delete(child); /* recursively dlt child's entire subtree */
	}
	free(tree->content); /* free content string allocated by strdup */
	free(tree); /* free node after all content is freed & no children exist */
}
