#include "linked.h"

static void print_menu() {
	printf("Доступные команды:\n");
	printf("\t0 - Завершить программу\n");
	printf("\t1 - Вывести список\n");
	printf("\t2 - Добавить число в начало списка\n");
	printf("\t3 - Добавить число в конец списка\n");
	printf("\t4 - Добавить число на N позицию\n");
	printf("\t5 - Удалить первый элемент списка\n");
	printf("\t6 - Удалить последний элемент списка\n");
}

static void print_link_list(t_node *lst) {
	if (!lst) {
		printf("EMPTY\n");
		return;
	}
	printf("%4d ", lst->value);
	while (lst->next) {
		lst = lst->next;
		printf("%4d ", lst->value);
	}
	printf("\n");
}

static t_node *pop_lst(t_node *lst, int value) {
	t_node *new_lst;

	new_lst = (t_node *)malloc(sizeof(t_node));
	new_lst->value = value;
	if (!lst) {
		new_lst->next = NULL;
	} else {
		new_lst->next = lst;
	}
	return new_lst;
}

static t_node *push_lst(t_node *lst, int value) {
	t_node *new_lst, *start;

	new_lst = (t_node *)malloc(sizeof(t_node));
	new_lst->value = value;
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

static t_node *push_n_lst(t_node *lst, int value, int position) {
	t_node *new_lst, *start, *tmp = NULL;

	new_lst = (t_node *)malloc(sizeof(t_node));
	new_lst->value = value;
	if (!lst) {
		new_lst->next = NULL;
		start = new_lst;
	} else {
		if (position <= 0) {
			lst = pop_lst(lst, value);
			return lst;
		}
		start = lst;
		while (position-- && lst->next) {
			tmp = lst;
			lst = lst->next;
		}
		if (!position && tmp) {
			new_lst->next = lst;
			tmp->next = new_lst;
		} else {
			push_lst(lst, value);
		}
	}
	return (start);
}

static t_node *remove_first(t_node *lst) {
	t_node *start;

	if (!lst || lst->next == NULL) {
		if (!lst) {
			return NULL;
		}
		free(lst);
		return NULL;
	}
	start = lst->next;
	free(lst);
	return start;
}

static t_node *remove_last(t_node *lst) {
	t_node *start, *tmp;

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

int main() {
	t_node *linked_list = NULL;
	int command, value, position;

	print_menu();
	while (1) {
		scanf("%d", &command);
		switch (command) {
			case 0:
				exit(0);
			case 1:
				print_link_list(linked_list);
				break;
			case 2:
				printf("Введите число: ");
				scanf("%d", &value);
				linked_list = pop_lst(linked_list, value);
				break;
			case 3:
				printf("Введите число: ");
				scanf("%d", &value);
				linked_list = push_lst(linked_list, value);
				break;
			case 4:
				printf("Введите число: ");
				scanf("%d", &value);
				printf("Введите позицию: ");
				scanf("%d", &position);
				linked_list = push_n_lst(linked_list, value, position);
				break;
			case 5:
				linked_list = remove_first(linked_list);
				break;
			case 6:
				linked_list = remove_last(linked_list);
				break;
			default:
				printf("Такая команда отсутствует\n");
		}
	}
}
