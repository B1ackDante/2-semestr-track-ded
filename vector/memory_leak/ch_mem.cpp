/**
 *	@file
 *	@brief memory leak utility
 *	@author Den
 *	@version 1.0
 *	@date March 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const int maxword = 20;

struct node
	{
		int _new;
		int _del;
		int str_num;
		char* pointer;
		char** name_f;

		struct node* right;
		struct node* left;
	};

struct node* add_tree(struct node* node, char n_d, char* name_f, char* pointer)
	{
		if(node == NULL)
			{
				node = (struct node*)calloc(1, sizeof(struct node));

				if(n_d == 'N')
					++(node->_new);
				else
					++(node->_del);

				node->right = NULL;
				node->left = NULL;

				node->str_num = 0;

				node->name_f = (char** )calloc(maxword, sizeof(char*));

				node->name_f[0] = strdup(name_f);

				node->pointer = strdup(pointer);

				return node;
			}

	 	if(strcmp(node->pointer, pointer) == 0)
			{
				if(n_d == 'N')
					++(node->_new);
				else
					++(node->_del);

				++(node->str_num);

				node->name_f[node->str_num] = strdup(name_f);

				return node;
			}

	 	if(strcmp(node->pointer, pointer) > 0)
			node->right = add_tree(node->right, n_d, name_f, pointer);
		else
			node->left = add_tree(node->left, n_d, name_f, pointer);

		return node;
	}

void check_node(struct node* node)
	{
		if(node == NULL) return;

		if(node->_new != node->_del)
			{
				printf("Warning: memory leak: pointer = %s\nin\n", node->pointer);
				for(int i = 0; i <= node->str_num; ++i)
					printf("%s\n", node->name_f[i]);
			}

		check_node(node->right);

		check_node(node->left);
	}


int main(void)
	{
		FILE* memory_leak = fopen("memory_leak.txt", "r");

		char symb = 0;
		char* str = (char*) calloc(maxword, sizeof(char));
		char* pointer = (char*) calloc(maxword, sizeof(char));

		struct node* node = NULL;

		while(fscanf(memory_leak,"%c %s %s\n", &symb, str, pointer) == 3) node = add_tree(node, symb, str, pointer);

		check_node(node);
	}
