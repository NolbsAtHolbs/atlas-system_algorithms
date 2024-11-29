#include "heap.h"

/**
 * heap_insert - Inserts a value into a Min Binary Heap
 * @heap: Pointer to the heap where the node is inserted
 * @data: Pointer to the data to store in the new node
 *
 * Return: Pointer to the created node containing data, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new, *curr, *queue[1024];
	int front = 0, end = 0;

	if (!heap || !data)
		return (NULL);
	new = binary_tree_node(NULL, data); /* create a new node */
	if (!new)
		return (NULL);
	if (!heap->root)
		heap->root = new; /* Set new node as root if heap is empty */
	else
	{
		curr = heap->root, queue[end++] = curr;
		while (front < end) /* Level-order traversal to find insertion point */
		{
			curr = queue[front++];
			if (!curr->left)
			{
				curr->left = new, new->parent = curr;
				break;
			}
			queue[end++] = curr->left;
			if (!curr->right)
			{
				curr->right = new, new->parent = curr;
				break;
			}
			queue[end++] = curr->right;
		}
	}
	while (new->parent && heap->data_cmp(new->data, new->parent->data) < 0)
	{ /* restore min-heap property by sifting up */
		void *temp = new->data;
		new->data = new->parent->data;
		new->parent->data = temp;
		new = new->parent;
	}
	heap->size++;
	return (new);
}
