#include "sequence.c"
#include "sequence.h"
#include "stdio.h"
#include <string.h>
//decommmentare i test di interesse.
#define TEST_READ
#define TEST_PROCESS
#define TEST_SAVE
#define TEST_PRINT


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define END   "\x1b[0m"


void test_save(char* string_seq, int to_reverse, char* filename);
void test_read_generale(char* filename);
void test_read_vuoto(char* filename);
void test_print(char* string_seq);
void test_process(char* seq_string);

int main() {
#if COMPITO == 'A'
	char* filename = "A_to_read.txt";
	char prove[][20] = {"(abc)\0","()\0","gdfe(fg)yyt(fh)\0","(fdg)gf(ghf)fhf\0","gd(hjn)(hjg)gf\0","fdgg\0"};
	int to_reverse = 0;
#else
	char* filename = "B_to_read.txt";
	char prove[][20] = { "[jo]\0","[eter]rte[trjur5]\0","[]ydy\0","[wwr]ytu[tht]rty\0","[][]\0" };
	int to_reverse = 1;
#endif	

	

#ifdef TEST_READ
	printf(YELLOW"TEST READ\n"END);
	test_read_generale(filename);
	//test_read_vuoto("empty_file.txt");
	//test_read_vuoto("fgegr.txt");	
	puts("\n");
#endif // TEST_READ

#ifdef TEST_PROCESS
	int i;
	printf(YELLOW"TEST PROCESS\n"END);
	for (i = 0; i < sizeof(prove)/20; i++) {
		test_process(prove[i]);
	}
	puts("\n");
#endif // TEST_PROCESS

#ifdef TEST_SAVE
	/*APPUNTO: se dice che il salvataggio non è andato a buon fine, ma aprendo il file sembra corretto, e' perchè manca la fclose*/
	printf(YELLOW"TEST SAVE\n"END);
	char* save_file = "student_save.txt";
	test_save(prove[4], to_reverse, save_file);
	puts("\n");
#endif // TEST_SAVE

#ifdef TEST_PRINT
	printf(YELLOW"TEST PRINT\n"END);
	test_print(prove[3]);
	puts("\n");
#endif // TEST_PRINT

}

void test_process(char* seq_string) {
	printf("test process con seq = %s: ", seq_string);
	struct list sol_seq, stu_seq;
	sol_seq = string_to_sequence(seq_string);
	stu_seq = string_to_sequence(seq_string);
	process_sequence(&stu_seq);
	process_sequence_sol(&sol_seq);
	if (are_equal(stu_seq, sol_seq))
		printf(GREEN"ok\n"END);
	else
	{
		printf(RED"Errore"END" nella process\n");
		printf("Risultato ottenuto: ");
		print_sequence_sol(stu_seq);
		printf(" l=%d", stu_seq.length);
		printf("\nRisultato atteso: ");
		print_sequence_sol(sol_seq);
		printf(" l=%d", sol_seq.length);
		puts("");
	}

}
void test_save(char* string_seq, int to_reverse, char* filename) {
	FILE* fp;
	if (fp = fopen(filename, "w")) {
		fprintf(fp, "");
		fclose(fp);
	}
	struct list seq_read, seq_to_save = string_to_sequence(string_seq);
	save_sequence(seq_to_save, filename);
	seq_read = read_sequence_sol(filename);
	if (to_reverse) seq_read = reverse_copy(seq_read);
	printf("save in %s: ", filename);
	if (are_equal(seq_to_save, seq_read)) {
		printf(GREEN"ok\n"END);
	}
	else {
		printf(RED"Errore\n"END);
		printf("Seq da salvare: ");
		print_sequence_sol(seq_to_save);
		printf("\nSeq salvata: ");
		print_sequence_sol(seq_read);
		puts("");
	}

}
void test_read_generale(char* filename) {
	struct list sol_seq, stu_seq;
	sol_seq = read_sequence_sol(filename);
	stu_seq = read_sequence(filename);
	printf("read - caso generale: ");
	if (are_equal(stu_seq, sol_seq))
		printf(GREEN"ok\n"END);
	else {
		printf(RED"errore"END", sequenza non letta correttamente\n");
		printf("sequenza letta: ");
		print_sequence_sol(stu_seq);
		printf(" l=%d", stu_seq.length);
		printf("\nsequenza attesa: ");
		print_sequence_sol(sol_seq);
		printf(" l=%d", sol_seq.length);
		puts("");
	}

}
void test_read_vuoto(char* filename) {
	struct list seq = read_sequence(filename);
	if (seq.head != NULL && seq.length != 0)
		printf(RED"Errore"END", mancata gestione file vuoto o inesistente\n");
	else printf("test file vuoto o inesistente: "GREEN"ok\n"END);
}
void test_print(char* string_seq) {
	struct list seq = string_to_sequence(string_seq);
	printf("stampa sol: ");
	print_sequence_sol(seq);
	puts("");
	printf("stampa stu: ");
	print_sequence(seq);
}
