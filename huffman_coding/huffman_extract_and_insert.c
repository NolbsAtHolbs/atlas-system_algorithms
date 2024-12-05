#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts two nodes and inserts a new one
 * @priority_queue: pointer to the priority queue (min-heap)
 * Return: 1 on success, else 0
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *new_node;
	symbol_t *symbol1, *symbol2, *new_symbol;
	size_t combined_freq;

	if (!priority_queue || priority_queue->size < 2)
		return (0); /* invalid priority queue or not enough nodes */
	node1 = heap_extract(priority_queue);
	if (!node1)
		return (0); /* failed to extract first node */
	node2 = heap_extract(priority_queue);
	if (!node2)
		return (heap_insert(priority_queue, node1), 0); /* node2 xtrctn fail */
	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;
	combined_freq = symbol1->freq + symbol2->freq; /* combine frequencies */
	new_symbol = symbol_create(-1, combined_freq);
	if (!new_symbol)
		return (heap_insert(priority_queue, node1),
			heap_insert(priority_queue, node2), 0); /* failed to make symbol */
	new_node = binary_tree_node(NULL, new_symbol);
	if (!new_node)
	{
		free(new_symbol);
		return (heap_insert(priority_queue, node1),
			heap_insert(priority_queue, node2), 0); /* failed to create node */
	}
	new_node->left = node1, new_node->right = node2; /* set children */
	node1->parent = new_node, node2->parent = new_node; /* set parents */
	if (!heap_insert(priority_queue, new_node))
	{
		free(new_node), free(new_symbol);
		return (heap_insert(priority_queue, node1),
			heap_insert(priority_queue, node2), 0); /* insert new node fail */
	}
	return (1);
}
