#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts two nodes and inserts a new one
 * @priority_queue: pointer to the priority queue (min-heap)
 * Return: 1 on success, else 0
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *heap_node1, *heap_node2;
	binary_tree_node_t *symbol_node1, *symbol_node2;
	binary_tree_node_t *new_tree_node, *new_heap_node;
	symbol_t *symbol1, *symbol2, *new_symbol;
	size_t combined_freq;

	if (!priority_queue || priority_queue->size < 2)
		return (0);
	/* extract two nodes from the heap */
	heap_node1 = heap_extract(priority_queue);
	if (!heap_node1)
		return (0);
	heap_node2 = heap_extract(priority_queue);
	if (!heap_node2)
	{	/* reinsert heap_node1 back into heap */
		heap_insert(priority_queue, heap_node1);
		return (0);
	}
	/* get symbol nodes from the heap nodes */
	symbol_node1 = (binary_tree_node_t *)heap_node1->data;
	symbol_node2 = (binary_tree_node_t *)heap_node2->data;
	/* get symbols from the symbol nodes */
	symbol1 = (symbol_t *)symbol_node1->data;
	symbol2 = (symbol_t *)symbol_node2->data;
	/* combine frequencies */
	combined_freq = symbol1->freq + symbol2->freq;
	/* create new symbol with data = -1 and combined frequency */
	new_symbol = symbol_create(-1, combined_freq);
	if (!new_symbol)
	{
		heap_insert(priority_queue, heap_node1);
		heap_insert(priority_queue, heap_node2);
		return (0);
	}
	/* create new tree node with the new symbol */
	new_tree_node = binary_tree_node(NULL, new_symbol);
	if (!new_tree_node)
	{
		free(new_symbol);
		heap_insert(priority_queue, heap_node1);
		heap_insert(priority_queue, heap_node2);
		return (0);
	}
	/* set the left and right children of the new tree node */
	new_tree_node->left = symbol_node1;
	new_tree_node->right = symbol_node2;
	symbol_node1->parent = new_tree_node;
	symbol_node2->parent = new_tree_node;
	/* create a new heap node with new_tree_node as its data */
	new_heap_node = binary_tree_node(NULL, new_tree_node);
	if (!new_heap_node)
	{
		free(new_tree_node);
		free(new_symbol);
		heap_insert(priority_queue, heap_node1);
		heap_insert(priority_queue, heap_node2);
		return (0);
	}
	/* insert the new heap node back into the priority queue */
	if (!heap_insert(priority_queue, new_heap_node))
	{
		free(new_heap_node);
		free(new_tree_node);
		free(new_symbol);
		heap_insert(priority_queue, heap_node1);
		heap_insert(priority_queue, heap_node2);
		return (0);
	}
	free(heap_node1); /* free the extracted heap nodes */
	free(heap_node2);
	return (1);
}
