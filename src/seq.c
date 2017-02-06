#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "seq.h"

Sequence* create_sequence() {
    Sequence* sequence = malloc(sizeof(Sequence));
    sequence->length = 0;
    sequence->chars = malloc(sizeof(char));
    sequence->chars[0] = '\0';

    return sequence;
}

void append(Sequence* sequence, char c) {
    sequence->chars = realloc(sequence->chars, sequence->length+2);
    sequence->chars[sequence->length] = c;
    sequence->chars[sequence->length+1] = '\0';
    sequence->length++;
}

unsigned int compute_hash_val(Sequence* sequence) {
    unsigned char* p = (unsigned char*)sequence->chars;
    unsigned h = 0;
    for(int i = 0; i < sequence->length; i++) {
        h = 33 * h+p[i];
    }

    return h;
}

bool sequences_are_equal(Sequence* first, Sequence* other) {
    if(first->length != other->length) {
        return false;
    }
    for(int i = 0; i < first->length; i++) {
        if(first->chars[i] != other->chars[i]) {
            return false;
        }
    }

    return true;
}

Sequence* copy_sequence(Sequence* orig) {
    Sequence* copy = create_sequence();
    for(int i = 0; i < orig->length; i++) {
        append(copy, orig->chars[i]);
    }

    return copy;
}

void delete_sequence(Sequence* sequence) {
    free(sequence->chars);
    free(sequence);
}

char first_char_of(Sequence* sequence) {
    return sequence->chars[0];
}

void output_sequence(Sequence* seq, FILE* output) {
    for(int i = 0; i < seq->length; i++) {
        fputc(seq->chars[i], output);
    }
}
