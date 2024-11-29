#include "sequence.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


#if COMPITO == 'A'
struct list read_sequence_sol(char* filename) {
	FILE* f = fopen(filename, "r");
	char c;
	struct list sequence;
	sequence.length = 0;
	sequence.head = NULL;
	if (f != NULL) {
		while (fscanf(f, "%c", &c) != EOF) {
			add_tail(&sequence, c);
		}
		fclose(f);
	}
	return sequence;
}
#else //COMPITO B
struct list read_sequence_sol(char* filename) {
	FILE* f = fopen(filename, "r");
	struct list sequence;
	sequence.length = 0;
	sequence.head = NULL;
	if (f != NULL) {
		char c;
		while (fscanf(f, "%c", &c) != EOF) {
			add_head(&sequence, c);
		}
		fclose(f);
	}
	return sequence;
}
#endif

#if COMPITO == 'A' 
void process_sequence_sol(struct list* sequence) {
	struct node* tmp = sequence->head;
	struct node* prec = NULL;

	while (tmp) {
		if (tmp->character == START_SYM) {
			while (tmp->next->character != STOP_SYM) {
				delete_node(tmp, tmp->next);
			}
			insert_after(tmp, SUB_SYM);
		}
		prec = tmp;
		tmp = tmp->next;
	}
}
#else //COMPITO B
void process_sequence_sol(struct list* sequence) {
	struct node* tmp;
	struct node* prec = NULL;
	bool addSym = false;

	while (sequence->head->character != START_SYM) {
		delete_head(sequence);
		addSym = true;
	}
	if (addSym)
		add_head(sequence, SUB_SYM);
	tmp = sequence->head;
	while (tmp) {
		if (tmp->character == STOP_SYM) {
			if (tmp->next == NULL) return;
			while (tmp->next != NULL && tmp->next->character != START_SYM) {
				delete_node(tmp, tmp->next);
				sequence->length--;
			}
			insert_after(tmp, SUB_SYM);
			sequence->length++;
		}
		prec = tmp;
		tmp = tmp->next;
	}
}
#endif


void save_sequence_sol(struct list sequence, char* filename) {
	FILE* f = fopen(filename, "w");
	struct node* tmp = sequence.head;
	if (!tmp) return;
	if (f != NULL) {
		while (tmp) {
			fprintf(f, "%c", tmp->character);
			tmp = tmp->next;
		}
		fclose(f);
	}
}

void print_sequence_sol(struct list sequence) {
	struct node* tmp = sequence.head;
	if (!tmp) return;
	while (tmp) {
		printf("%c", tmp->character);
		tmp = tmp->next;
	}
}
