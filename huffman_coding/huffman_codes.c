#include "huffman.h"

void print_codes(binary_tree_node_t *node, int *code, size_t depth);
void free_huffman_tree(binary_tree_node_t *tree);

/**
 * huffman_codes - builds the huffman tree and prints the codes
 * @data: array of characters
 * @freq: array of frequencies
 * @size: size of the arrays
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *tree;

	if (!data || !freq || size == 0)
		return (0); /* invalid input */
	tree = huffman_tree(data, freq, size);
	if (!tree)
		return (0); /* failed to build huffman tree */
	print_codes(tree, NULL, 0);
	free_huffman_tree(tree);
	return (1);
}

/**
 * print_codes - recursively prints the huffman codes
 * @node: pointer to the current node
 * @code: array to store the current code
 * @depth: current depth of the recursion
 */
void print_codes(binary_tree_node_t *node, int *code, size_t depth)
{
	symbol_t *symbol;
	size_t i;

	if (!node)
		return;
	if (!code)
	{
		code = malloc(sizeof(int) * 256);
		if (!code)
			return;
	}
	if (!node->left && !node->right)
	{
		symbol = (symbol_t *)node->data;
		printf("%c: ", symbol->data);
		for (i = 0; i < depth; i++)
			printf("%d", code[i]);
		printf("\n");
	}
	else
	{
		if (node->left)
		{
			code[depth] = 0;
			print_codes(node->left, code, depth + 1);
		}
		if (node->right)
		{
			code[depth] = 1;
			print_codes(node->right, code, depth + 1);
		}
	}
	if (depth == 0)
		free(code);
}

/**
 * free_huffman_tree - frees the huffman tree
 * @tree: pointer to the root node of the tree
 */
void free_huffman_tree(binary_tree_node_t *tree)
{
	if (!tree)
		return;
	free_huffman_tree(tree->left);
	free_huffman_tree(tree->right);
	free(tree->data);
	free(tree);
}
