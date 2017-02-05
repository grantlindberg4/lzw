#ifndef SEQ_H
#define SEQ_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {
	char* chars;
	int length;
} Sequence;

Sequence* create_sequence();
void append(Sequence* sequence, char c);
unsigned int compute_hash_val(Sequence* sequence);
_Bool sequences_are_equal(Sequence* first, Sequence* other);
Sequence* copy_sequence(Sequence* orig);
void delete_sequence(Sequence* sequence);
char first_char_of(Sequence* sequence);
void output_sequence(Sequence* seq, FILE* output);

#endif
