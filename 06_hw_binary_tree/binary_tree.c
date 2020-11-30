#include "binary_tree.h"

static void print_menu() {
	printf("Доступные команды:\n");
	printf("\t0 - Выйти из программы\n");
	printf("\t1 - Добавить элемент в дерево\n");
	printf("\t2 - Обход в ширину\n");
	printf("\t3 - Обход в глубину\n");
	printf("\t4 - Найти элемент\n");
}

static t_b_tree *add_elem(t_b_tree *tree, int value) {
	t_b_tree *start, *tmp;

	if (!tree) {
		tree = (t_b_tree *)malloc(sizeof(t_b_tree));
		tree->value = value;
		tree->right = NULL;
		tree->left = NULL;
		return tree;
	}
	start = tree;
	while (tree) {
		tmp = tree;
		if (tree->value <= value) {
			tree = tree->right;
		} else {
			tree = tree->left;
		}
	}
	tree = (t_b_tree *)malloc(sizeof(t_b_tree));
	tree->value = value;
	tree->right = NULL;
	tree->left = NULL;
	if (tmp->value <= value) {
		tmp->right = tree;
	} else {
		tmp->left = tree;
	}
	return start;
}

static void dfs(t_b_tree *tree) {
	printf("%d ", tree->value);
	if (tree->left) {
		dfs(tree->left);
	}
	if (tree->right) {
		dfs(tree->right);
	}
}

static void queue_push(queue_t* q, const void* ptr){
	node_t* p = (node_t*)malloc(sizeof(node_t));
	if(p != NULL){
		p->ptr  = ptr;
		p->next = NULL;
		if(q->head == NULL)
			q->head = q->tail = p;
		else {
			q->tail->next = p;
			q->tail = p;
		}
	}
}

static void queue_init(queue_t* q) {
	q->head = q->tail = NULL;
}

static int queue_empty(queue_t* q) {
	return (q->head == NULL);
}

static void *queue_front(queue_t* q) {
	return q->head->ptr;
}

static void queue_pop(queue_t* q) {
	node_t* t;

	if(q->head != NULL){
		t       = q->head;
		q->head = q->head->next;
		free(t);
		if(q->head == NULL)
			q->tail = NULL;
	}
}

static void bfs(t_b_tree *tree) {
	t_b_tree *p;
	queue_t q;
	queue_init(&q);

	queue_push(&q, tree);
	while(!queue_empty(&q)){
		p = (t_b_tree *)queue_front(&q);
		queue_pop(&q);
		printf("%d ", p->value);

		if(p->left != NULL)
			queue_push(&q, p->left);
		if(p->right != NULL)
			queue_push(&q, p->right);
	}
}

static void find_elem(t_b_tree *tree, int value) {
	int depth = -1;

	while (tree) {
		depth++;
		if (tree->value > value) {
			tree = tree->left;
		} else if (tree->value < value) {
			tree = tree->right;
		} else {
			printf("Глубина: %d\n", depth);
			return;
		}
	}
	printf("Элемент отсутствует\n");
}

int main() {
	t_b_tree *tree = NULL;
	int command, value;

	print_menu();
	while (1) {
		scanf("%d", &command);
		switch (command) {
			case 0:
				exit(0);
			case 1:
				printf("Введите число: ");
				scanf("%d", &value);
				tree = add_elem(tree, value);
				break;
			case 2:
				if (tree) {
					bfs(tree);
				} else {
					printf("EMPTY");
				}
				printf("\n");
				break;
			case 3:
				if (tree) {
					dfs(tree);
				} else {
					printf("EMPTY");
				}
				printf("\n");
				break;
			case 4:
				printf("Введите элемент поиска: ");
				scanf("%d", &value);
				if (tree) {
					find_elem(tree, value);
				} else {
					printf("Элемент отсутствует\n");
				}
				break;
			default:
				printf("Такая команда отсутствует\n");
		}
	}
}
