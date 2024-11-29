#include "heap.h"

/**
 * heap_insert - inserts a value into a Min Binary Heap
 * @heap: pointer to heap in which the node has to be inserted
 * @data: pointer containing the data to store in the new node
 * Return: pointer to created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *current_node, *node_queue[1024];
	int front = 0, end = 0;

	if (data == NULL || heap == NULL)
		return (NULL);
	new_node = binary_tree_node(NULL, data);
	if (new_node == NULL)
		return (NULL);
	if (!heap->root)
		heap->root = new_node;
	else
	{
		current_node = heap->root; /* level-order trvrse to find insrt point */
		node_queue[end++] = current_node;
		while (front < end)
		{
			current_node = node_queue[front++];
			if (!current_node->left)
			{
				current_node->left = new_node;
				new_node->parent = current_node;
				break;
			}
			else
				node_queue[end++] = current_node->left;
			if (!current_node->right)
			{
				current_node->right = new_node;
				new_node->parent = current_node;
				break;
			}
			else
				node_queue[end++] = current_node->right;
		}
	} /* restore the min-heap property by sifting up */
	while (new_node->parent && heap->data_cmp(
			new_node->data, new_node->parent->data) < 0)
	{
		void *temp_data = new_node->data;
		new_node->data = new_node->parent->data;
		new_node->parent->data = temp_data;
		new_node = new_node->parent;
	}
	heap->size++;
	return (new_node);
}
