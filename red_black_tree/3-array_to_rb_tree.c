#include "rb_trees.h"

/**
 * array_to_rb_tree - builds a binary search tree from an array
 * @array: pointer to the first element of the array to be converted
 * @size: number of elements in the array
 * Return: pointer to the root node of the created R-B tree, or NULL on failure
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	size_t i;
	rb_tree_t *tree = NULL; /* init tree pointer to null */

	if (array == NULL)
		return (NULL); /* null check */
	for (i = 0; i < size; i++)
		rb_tree_insert(&tree, array[i]); /* insert each val into tree */
	return (tree);
}