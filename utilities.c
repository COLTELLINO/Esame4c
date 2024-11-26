#include "utilities.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 struct node* node_alloc(char character) {
	struct node* n = (struct node*)calloc(1, sizeof(struct node));
	if (n == NULL) return NULL;
	n->character = character;
	n->next = NULL;
	return n;
}
 void insert_after(struct node* node, char character) {
	struct node* new_node = node_alloc(character);
	if (new_node == NULL) return;
	new_node->next = node->next;
	node->next = new_node;
}
 void add_head(struct list* sequence, char character) {
	struct node* new_char = node_alloc(character);
	if (new_char == NULL) return;
	new_char->next = sequence->head;
	sequence->head = new_char;
	sequence->length++;
}
 void add_tail(struct list* sequence, char character) {
	if (sequence->length == 0) {
		sequence->head = node_alloc(character);
		if (sequence->head) sequence->length++;
		return;
	}
	struct node* tmp = sequence->head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	insert_after(tmp, character);
	if (tmp->next != NULL) sequence->length++;

}
 void delete_head(struct list* sequence) {
	struct node* to_delete = sequence->head;
	sequence->head = to_delete->next;
	free(to_delete);
}
 void delete_node(struct node* prec, struct node* node) {
	prec->next = node->next;
	free(node);
}
 
 struct list string_to_sequence(char* string_seq) {
	 unsigned int i;
	 struct list s;
	 s.head = NULL;
	 s.length = 0;
	 while (*(string_seq) != '\0') {
		 add_tail(&s, *(string_seq));
		 string_seq++;
	 }
	 return s;
 }

 int are_equal(struct list seq1, struct list seq2) {
	 if (seq1.length != seq2.length) return 0;
	 
	 struct node* tmp1 = seq1.head;
	 struct node* tmp2 = seq2.head;
	 if (!tmp1 || !tmp2) return 0;
	 while (tmp1 && tmp2) {
		 if (tmp1->character != tmp2->character) return 0;
		 tmp1 = tmp1->next;
		 tmp2 = tmp2->next;
	 }
	 return 1;
 }

 struct list reverse_copy(struct list sequence) {
	 struct list rev_seq = { NULL, 0 };
	 struct node* tmp = sequence.head;
	 if (!tmp) return rev_seq;
	 while (tmp) {
		 add_head(&rev_seq, tmp->character);
		 tmp = tmp->next;
	 }
	 return rev_seq;
 }