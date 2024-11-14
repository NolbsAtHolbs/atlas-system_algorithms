#include "rb_trees.h"

void right_rotate(rb_tree_t **tree, rb_tree_t *y);
void left_rotate(rb_tree_t **tree, rb_tree_t *x);
void rb_insert_fixup(rb_tree_t **tree, rb_tree_t *node);

/**
 * rb_tree_insert - inserts a value in a Red-Black Tree
 * @tree: double pointer to the root node of the Red-Black tree
 * @value: value to insert
 * Return: pointer to the created node, or NULL on failure
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new_node, *parent, *current;

	if (tree == NULL)
		return (NULL);
	current = *tree; /* check if value already exists */
	parent = NULL;
	while (current != NULL)
	{
		parent = current;
		if (value == current->n)
			return (NULL);
		else if (value < current->n)
			current = current->left;
		else
			current = current->right;
	}
	new_node = rb_tree_node(parent, value, RED); /* create new node */
	if (new_node == NULL)
		return (NULL);
	if (parent == NULL) /* insert new node */
		*tree = new_node;
	else if (value < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;
	rb_insert_fixup(tree, new_node); /* fix red-black tree properties */

	return (new_node);
}

/**
 * rb_insert_fixup - fixes the Red-Black Tree after insertion
 * @tree: double pointer to the root of the tree
 * @node: pointer to the newly inserted node
 */
void rb_insert_fixup(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *uncle;

	while (node != *tree && node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)
		{
			uncle = node->parent->parent->right;
			if (uncle && uncle->color == RED)
			{
				node->parent->color = BLACK; /* case 1: uncle is red */
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->right)
				{
					node = node->parent; /* case 2: node is right child */
					left_rotate(tree, node);
				}
				node->parent->color = BLACK; /* case 3: node is left child */
				node->parent->parent->color = RED;
				right_rotate(tree, node->parent->parent);
			}
		}
		else
		{
			uncle = node->parent->parent->left;
			if (uncle && uncle->color == RED)
			{
				node->parent->color = BLACK; /* mirror case 1: uncle is red */
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left)
				{
					node = node->parent; /* mirror case 2: node is left child */
					right_rotate(tree, node);
				}
				node->parent->color = BLACK; /* mcase 3: node is right chld */
				node->parent->parent->color = RED;
				left_rotate(tree, node->parent->parent);
			}
		}
	}
	(*tree)->color = BLACK;
}

/**
 * left_rotate - performs a left rotation on a node
 * @tree: double pointer to the root of the tree
 * @x: pointer to the node to rotate
 */
void left_rotate(rb_tree_t **tree, rb_tree_t *x)
{
	rb_tree_t *y = x->right;

	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)
		*tree = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

/**
 * right_rotate - performs a right rotation on a node
 * @tree: double pointer to the root of the tree
 * @y: pointer to the node to rotate
 */
void right_rotate(rb_tree_t **tree, rb_tree_t *y)
{
	rb_tree_t *x = y->left;

	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;
	x->parent = y->parent;
	if (y->parent == NULL)
		*tree = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;
	x->right = y;
	y->parent = x;
}
