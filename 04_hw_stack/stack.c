#include "stack.h"

static t_stack *convert_to_struct(char *str) {
	t_stack *stack = NULL, *tmp, *ptr = NULL;

	while (*str) {
		if (!(*str == '[' || *str == ']'
		|| *str == '{' || *str == '}'
		|| *str == '(' || *str == ')')) {
			printf("Некорректный ввод: %c\n", *str);
			exit(0);
		}
		tmp = (t_stack *)malloc(sizeof(t_stack));
		tmp->data = *str;
		tmp->next = NULL;
		if (!stack) {
			stack = tmp;
		} else {
			if (!ptr) {
				ptr = tmp;
				stack->next = tmp;
			} else {
				ptr->next = tmp;
				ptr = tmp;
			}
		}
		str++;
	}
	return stack;
}

static int match_bracket(char a, char b) {
	return ((a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']'));
}

static t_stack *push_back(t_stack *lst, char a) {
	t_stack *new_lst, *start;

	new_lst = (t_stack *)malloc(sizeof(t_stack));
	new_lst->data = a;
	if (!lst) {
		new_lst->next = NULL;
		start = new_lst;
	} else {
		start = lst;
		while (lst->next) {
			lst = lst->next;
		}
		lst->next = new_lst;
	}
	return start;
}

static char get_last_elem(t_stack *stack) {
	while (stack->next) {
		stack = stack->next;
	}
	 return stack->data;
}

static t_stack *remove_last_elem(t_stack *lst) {
	t_stack *start, *tmp;

	if (!lst || lst->next == NULL) {
		if (!lst) {
			return NULL;
		}
		free(lst);
		return NULL;
	}
	start = lst;
	while (lst->next) {
		tmp = lst;
		lst = lst->next;
	}
	tmp->next = NULL;
	free(lst);
	return start;
}

static int check_brackets(t_stack *stack) {
	t_stack *ptr = NULL;

	if (!stack || stack->next == NULL) {
		printf("NOT OK\n");
		exit(0);
	}
	while (stack) {
		if (stack->data == '(' || stack->data == '[' || stack->data == '{') {
			ptr = push_back(ptr, stack->data);
		}
		if (stack->data == ')' || stack->data == ']' || stack->data == '}') {
			if (!ptr) {
				return 0;
			}
			if (!match_bracket(get_last_elem(ptr), stack->data)) {
				return 0;
			} else {
				ptr = remove_last_elem(ptr);
			}
		}
		stack = stack->next;
	}
	return (!ptr);
}

int main(int ac, char **av) {
	t_stack *stack;

	stack = NULL;
	if (ac == 2) {
		stack = convert_to_struct(av[1]);
		if (check_brackets(stack)) {
			printf("OK\n");
		} else {
			printf("NOT OK\n");
		}
	} else {
		printf("Некорретный ввод\n");
	}
	return 0;
}
