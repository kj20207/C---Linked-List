
typedef struct linked_node{
	struct linked_node *next;
	int value;
} linked_node;

typedef struct linked_list{
	struct linked_node *head;
	struct linked_node *tail;
	int size;
} linked_list;

int list_create(struct linked_list **list);

int list_insert(struct linked_list **list, int value);

int list_remove(struct linked_list **list, int value);

int list_contains(struct linked_list **list, int value);

int list_size(struct linked_list **list);

int list_destroy(struct linked_list **list);