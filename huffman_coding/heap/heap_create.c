#include "heap.h"

/**
 * heap_create - creates a heap data structure
 * @data_cmp: pointer to a function to compare two nodes' data
 * Return: pointer to the created heap_t structure, or NULL on failure
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap;

	if (data_cmp == NULL)
		return (NULL);
	heap = malloc(sizeof(heap_t));
	if (heap == NULL)
		return (NULL);
	heap->size = 0;
	heap->root = NULL;
	heap->data_cmp = data_cmp;
	return (heap);
}
