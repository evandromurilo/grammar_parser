#ifndef M_LIST_H
#define M_LIST_H

struct LinkedNode {
	struct LinkedNode *next;
	struct LinkedNode *prev;
	void *value;
};

struct LinkedList {
	struct LinkedNode *first;
	struct LinkedNode *last;
	int length;
};

// init_list: initializes a new LinkedList
// returns a pointer to the new LinkedList
struct LinkedList *init_list();

// list_append: appends 'value' to 'list'
void list_append(struct LinkedList *list, void *value);

// list_prepend: prepends 'value' to 'list'
void list_prepend(struct LinkedList *list, void *value);

// list_popf: removes the first value from 'list'
// returns the removed value
void *list_popf(struct LinkedList *list);

// list_popl: removes the last value from 'list'
// returns the removed value
void *list_popl(struct LinkedList *list);

// list_contains: returns true if calling comparison_function with 'value' and
// some value in 'list' returns true
bool list_contains(struct LinkedList *list, void *value, bool(*comparison_function)(void *, void *));

int split_linked(struct LinkedList *list, char* str, char *goal);

#endif
