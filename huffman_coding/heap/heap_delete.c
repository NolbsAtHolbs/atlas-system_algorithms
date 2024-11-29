#include "heap.h"

void delete_node(binary_tree_node_t *node, void (*free_data)(void *));

/**
 * heap_delete - deallocates a heap
 * @heap: pointer to the heap to delete
 * @free_data: pointer to a function that frees the data in a node
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;
	if (heap->root)
		delete_node(heap->root, free_data);
	free(heap);
}

/**
 * delete_node - recursively frees nodes in post-order traversal
 * @node: pointer to the current node
 * @free_data: pointer to a function that frees the data in a node
 */
void delete_node(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;
	delete_node(node->left, free_data); /* rcrsvly dlt left & right subtrees */
	delete_node(node->right, free_data);
	if (free_data) /* free the data if free_data function is provided */
		free_data(node->data);
	free(node); /* free the node */
}
