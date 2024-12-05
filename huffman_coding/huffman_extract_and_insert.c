#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts two nodes and inserts a new one
 * @priority_queue: pointer to the priority queue (min-heap)
 * Return: 1 on success, else 0
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2;
	binary_tree_node_t *new_node;
	symbol_t *symbol1, *symbol2, *new_symbol;
	size_t combined_freq;

	if (!priority_queue || priority_queue->size < 2)
		return (0);
	/* extract two nodes from the heap */
	node1 = heap_extract(priority_queue);
	if (!node1)
		return (0);
	node2 = heap_extract(priority_queue);
	if (!node2)
	{
		/* reinsert node1 back into the heap */
		heap_insert(priority_queue, node1);
		return (0);
	}
	/* get the symbols from the nodes */
	symbol1 = (symbol_t *)node1->data;
	symbol2 = (symbol_t *)node2->data;
	/* combine frequencies */
	combined_freq = symbol1->freq + symbol2->freq;
	/* Create a new symbol with data = -1 and combined frequency */
	new_symbol = symbol_create(-1, combined_freq);
	if (!new_symbol)
	{
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}
	/* create a new node with the new symbol */
	new_node = binary_tree_node(NULL, new_symbol);
	if (!new_node)
	{
		free(new_symbol);
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}
	/* set the left and right children of the new node */
	new_node->left = node1;
	new_node->right = node2;
	node1->parent = new_node;
	node2->parent = new_node;
	/* insert the new node back into the priority queue */
	if (!heap_insert(priority_queue, new_node))
	{
		free(new_node);
		free(new_symbol);
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}
	return (1);
}
