#include "heap.h"

void bubble_down(heap_t *heap, binary_tree_node_t *node);

/**
 * heap_extract - extracts the root value from the Min Binary Heap
 * @heap: pointer to the heap to extract the value from
 * Return: pointer to the extracted value, or NULL if it fails
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last_node, *current_node;
	binary_tree_node_t **node_queue;
	size_t queue_size, front = 0, rear = 0;

	if (!heap || !heap->root)
		return (NULL);
	data = heap->root->data;
	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
	}
	else
	{
		queue_size = heap->size; /* dynallocate the queue based on heap size */
		node_queue = malloc(sizeof(*node_queue) * queue_size);
		if (!node_queue)
			return (NULL);
		current_node = heap->root; /* level-order traverse to find last node */
		node_queue[rear++] = current_node;
		while (front < rear)
		{
			current_node = node_queue[front++];
			if (current_node->left)
				node_queue[rear++] = current_node->left;
			if (current_node->right)
				node_queue[rear++] = current_node->right;
		}
		last_node = current_node;
		heap->root->data = last_node->data; /* rplc root data w/ last node's */
		if (last_node->parent->left == last_node) /* rmov last node frm prnt */
			last_node->parent->left = NULL;
		else
			last_node->parent->right = NULL;
		free(last_node);
		free(node_queue);
	}
	heap->size--;
	if (heap->root) /* restore heap property */
		bubble_down(heap, heap->root);
	return (data);
}

/**
 * bubble_down - Restores the min-heap property by sifting down
 * @heap: Pointer to the heap
 * @node: Pointer to the node to sift down
 */
void bubble_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *min_child;
	void *temp_data;

	while (node->left || node->right)
	{
		if (node->left && node->right) /* find smallest child */
		{
			if (heap->data_cmp(node->left->data, node->right->data) <= 0)
				min_child = node->left;
			else
				min_child = node->right;
		}
		else if (node->left)
			min_child = node->left;
		else
			min_child = node->right;
		if (heap->data_cmp(node->data, min_child->data) > 0)
		{ /* compare node with smallest child */
			temp_data = node->data; /* swap data */
			node->data = min_child->data;
			min_child->data = temp_data;
			node = min_child;
		}
		else
			break;
	}
}
