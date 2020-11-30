#ifndef STACK_H
# define STACK_H

# include <stdio.h>
# include <stdlib.h>

typedef struct	s_stack {
	char data;
	struct s_stack *next;
}				t_stack;

#endif
