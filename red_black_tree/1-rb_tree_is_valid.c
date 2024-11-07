#include "rb_trees.h"

int rbt_node_validator(const rb_tree_t *node, int min, int max, int *black_height);

/**
 * rbt_node_validator - validate red-black tree properties
 * @node: pointer to current node
 * @min: minimum allowable value for node->n
 * @max: maximum allowable value for node->n
 * @black_height: pointer to store the black height
 * Return: 1 if subtree is valid, else 0
 */
int rbt_node_validator(const rb_tree_t *node, int min, int max, int *black_height)
{
	int left_black_height, right_black_height;

	if (node == NULL)
	{
		*black_height = 0;
		return (1);
	}
	if (node->n <= min || node->n >= max) /* check BST property */
		return (0);
	if (node->color != RED && node->color != BLACK) /* check node color */
		return (0);
	if (node->color == RED) /* check for consecutive red nodes */
	{
		if ((node->left && node->left->color == RED) ||
		    (node->right && node->right->color == RED))
			return (0);
	}
	/* recursively validate left and right subtrees */
	if (!rbt_node_validator(node->left, min, node->n, &left_black_height) ||
	    !rbt_node_validator(node->right, node->n, max, &right_black_height))
		return (0);
	if (left_black_height != right_black_height) /* check black heights */
		return (0);
	*black_height = left_black_height; /* find black height for current node */
	if (node->color == BLACK)
		*black_height += 1;
	return (1);
}

/**
 * rb_tree_is_valid - checks if a binary tree is a valid Red-Black Tree
 * @tree: pointer to the root node of the tree to check
 * Return: 1 if tree is a valid red-black tree, else 0
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int black_height;

	if (tree == NULL)
		return (0);
	if (tree->color != BLACK) /* root must be black */
		return (0);
	return (is_valid_rb_tree(tree, INT_MIN, INT_MAX, &black_height));
}
