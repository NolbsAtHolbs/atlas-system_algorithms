#include "huffman.h"

/**
 * huffman_tree - builds the Huffman tree
 * @data: array of characters
 * @freq: array of frequencies
 * @size: size of the arrays
 * Return: pointer to root node of Huffman tree, or NULL on failure
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	heap_t *priority_queue = NULL;

	if (!data || !freq || size == 0)
		return (NULL); /* invalid input */
	priority_queue = huffman_priority_queue(data, freq, size); /* create PQ */
	if (!priority_queue)
		return (NULL); /* failed to create PQ */
	while (priority_queue->size > 1) /* build the huffman tree */
		if (!huffman_extract_and_insert(priority_queue))
			return (NULL); /* failed during extraction and insertion */
	root = heap_extract(priority_queue); /* xtract root node of huffman tree */
	heap_delete(priority_queue, NULL);
	return (root);
}
