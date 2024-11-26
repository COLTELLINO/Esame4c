#ifndef UTILS
#define UTILS
#include "utilities.h"
#endif // !UTILS


struct list read_sequence_sol(char* filename);

void save_sequence_sol(struct list sequence, char* filename);

void process_sequence_sol(struct list* sequence);

void print_sequence_sol(struct list sequence);