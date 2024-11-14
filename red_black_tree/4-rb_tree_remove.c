#include "rb_trees.h"

rb_tree_t *rb_tree_search(rb_tree_t *root, int n);

/**
 * rb_tree_remove - removes a node from a red-black tree
 * @root: pointer to the root node of the tree
 * @n: value to search and remove from the tree
 * Return: pointer to the root node of the tree after deletion
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *node_to_delete;

	if (root == NULL)
		return (NULL);
	node_to_delete = rb_tree_search(root, n); /* find node to delete */
	/* check if the node is a red leaf */
	if (node_to_delete && node_to_delete->color == RED &&
	    node_to_delete->left == NULL && node_to_delete->right == NULL)
	{
		if (node_to_delete->parent == NULL)
		{
			free(node_to_delete); /* node is root */
			return (NULL);
		}
		else
		{
			/* remove the red leaf node */
			if (node_to_delete == node_to_delete->parent->left)
				node_to_delete->parent->left = NULL;
			else
				node_to_delete->parent->right = NULL;
			free(node_to_delete);
			return (root);
		}
	}
	return (root); /* if node is not a red leaf, do nothing */
}

/**
 * rb_tree_search - searches for a node with a given value in a red-black tree
 * @root: pointer to the root node of the tree
 * @n: value to search for
 *
 * Return: (pointer to the node with value n, or NULL if not found)
 */
rb_tree_t *rb_tree_search(rb_tree_t *root, int n)
{
	if (root == NULL || root->n == n)
		return (root);
	if (n < root->n)
		return (rb_tree_search(root->left, n));
	else
		return (rb_tree_search(root->right, n));
}
