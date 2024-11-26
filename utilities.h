#ifndef SELECTOR
#define SELECTOR
#include "selector.h"
#endif // !SELECTOR


struct node {
	char character;
	struct node* next;
};

struct list {
	struct node* head;
	int length;
};

struct node* node_alloc(char character);
 void insert_after(struct node* node, char character);
 void add_head(struct list* sequence, char character);
 void add_tail(struct list* sequence, char character);
 void delete_head(struct list* sequence);
 void delete_node(struct node* prec, struct node* node);
 struct list string_to_sequence(char* string_seq);
 struct list reverse_copy(struct list sequence);
 int are_equal(struct list seq1, struct list seq2);