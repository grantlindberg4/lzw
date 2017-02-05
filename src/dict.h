#ifndef DICT_H
#define DICT_H

#include <stdbool.h>

#include "seq.h"

// #define NUM_ENTRIES 46001
#define NUM_CHARS 256
#define NUM_ENTRIES 256
// #define NUM_CHARS 60
#define MAX_CODE 65536

typedef struct Entry {
    Sequence* sequence;
    int code;
    struct Entry* next;
} Entry;

typedef struct Dict {
    int size;
    Entry** array;
} Dict;

Dict* initialize_dictionary();
Dict* create_dictionary();
void destroy_dictionary(Dict* dictionary);
void insert_to_dictionary(Dict* dictionary, Sequence* sequence, unsigned int code);
Entry* create_entry(Sequence* sequence, unsigned int code);
_Bool occupied_at(Dict* dictionary, int index);
_Bool search_for_key(Dict* dictionary, Sequence* sequence, unsigned int* code);
void delete_entry(Entry* entry);
_Bool space_in(Dict* dictionary, int num_codes);

void print_dictionary(Dict* dictionary);

#endif
