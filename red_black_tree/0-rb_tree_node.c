#include "rb_trees.h"

/**
 * rb_tree_node - creates a red-black tree node
 * @parent: pointer to parent node of the node to create
 * @value: value to put in the new node
 * @color: color of the node
 * Return: pointer to the new node, or NULL on failure
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new_node;

	new_node = malloc(sizeof(rb_tree_t));
	if (new_node == NULL)
		return (NULL);
	new_node->parent = parent;
	new_node->n = value;
	new_node->color = color;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
