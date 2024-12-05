#include "huffman.h"

/**
 * symbol_create - creates a symbol_t data structure
 * @data: the character to be stored
 * @freq: the associated frequency
 * Return: pointer to the created symbol_t structure, or NULL on failure
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol;

	symbol = malloc(sizeof(symbol_t));
	if (!symbol)
		return (NULL);

	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}
