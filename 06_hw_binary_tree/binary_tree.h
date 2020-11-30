#ifndef BINARY_TREE
# define BINARY_TREE

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define BUF 12

typedef struct	s_b_tree {

	int value;
	struct s_b_tree *left;
	struct s_b_tree *right;
}				t_b_tree;

typedef struct node {
	void*  ptr;
	struct node* next;
} node_t;

typedef struct {
	node_t* head;
	node_t* tail;
} queue_t;

#endif
