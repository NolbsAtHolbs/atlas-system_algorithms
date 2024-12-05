#include "huffman.h"

/**
 * symbol_cmp - comparison function for symbols based on frequency
 * @p1: pointer to the first binary_tree_node_t *
 * @p2: pointer to the second binary_tree_node_t *
 * Return: difference between the frequencies of the two symbols
 */
static int symbol_cmp(void *p1, void *p2)
{
	binary_tree_node_t *node1 = (binary_tree_node_t *)p1;
	binary_tree_node_t *node2 = (binary_tree_node_t *)p2;
	symbol_t *symbol1 = (symbol_t *)node1->data;
	symbol_t *symbol2 = (symbol_t *)node2->data;

	if (symbol1->freq > symbol2->freq) /* compare frequencies */
		return (1);
	else if (symbol1->freq < symbol2->freq)
		return (-1);
	else
	{   /* frequencies are equal, compare data */
		if ((unsigned char)symbol1->data > (unsigned char)symbol2->data)
			return (1);
		else if ((unsigned char)symbol1->data < (unsigned char)symbol2->data)
			return (-1);
		else
			return (0);
	}
}

/**
 * huffman_priority_queue - creates a priority queue for huffman coding
 * @data: array of characters
 * @freq: array of frequencies
 * @size: size of the arrays
 * Return: pointer to the created min-heap (priority queue), or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);
	heap = heap_create(symbol_cmp);
	if (!heap)
		return (NULL);
	for (i = 0; i < size; i++)
	{
		symbol_t *symbol = symbol_create(data[i], freq[i]);
		binary_tree_node_t *node;

		if (!symbol)
			return (heap_delete(heap, NULL), NULL);
		node = binary_tree_node(NULL, symbol);
		if (!node)
		{
			free(symbol);
			return (heap_delete(heap, NULL), NULL);
		}
		if (!heap_insert(heap, node))
		{
			free(symbol);
			free(node);
			return (heap_delete(heap, NULL), NULL);
		}
	}
	return (heap);
}
