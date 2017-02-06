#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "dict.h"

void insert_to_dictionary(Dict* dictionary, Sequence* sequence, unsigned int code) {
    Entry* entry = create_entry(sequence, code);
    unsigned hash_val = compute_hash_val(sequence) % dictionary->size;
    entry->next = dictionary->array[hash_val];
    dictionary->array[hash_val] = entry;
}

bool search_for_key(Dict* dictionary, Sequence* sequence, unsigned int* code) {
    unsigned hash_val = compute_hash_val(sequence) % dictionary->size;
    Entry* current = dictionary->array[hash_val];
    while(current != NULL) {
        if(sequences_are_equal(current->sequence, sequence)) {
            *code = current->code;
            return true;
        }
        current = current->next;
    }

    return false;
}

Entry* create_entry(Sequence* sequence, unsigned int code) {
    Entry* entry = malloc(sizeof(Entry));
    entry->sequence = sequence;
    entry->code = code;
    entry->next = NULL;

    return entry;
}

Dict* create_dictionary() {
    Dict* dictionary = malloc(sizeof(Dict));
    dictionary->size = NUM_ENTRIES;
    dictionary->array = (Entry**)calloc(dictionary->size, sizeof(Entry*));

    return dictionary;
}

Dict* initialize_dictionary() {
    Dict* dictionary = create_dictionary();
    for(int i = 0; i < NUM_CHARS; i++) {
        char c = i;
        Sequence* sequence = create_sequence();
        append(sequence, c);
        insert_to_dictionary(dictionary, sequence, i);
    }

    return dictionary;
}

void destroy_dictionary(Dict* dictionary) {
    for(int i = 0; i < NUM_ENTRIES; i++) {
        Entry* current = dictionary->array[i];
        while(current != NULL) {
            Entry* next = current->next;
            delete_entry(current);
            current = next;
        }
    }
    free(dictionary->array);
    free(dictionary);
}

void delete_entry(Entry* entry) {
    delete_sequence(entry->sequence);
    free(entry);
}

bool space_in(Dict* dictionary, int num_codes) {
    return num_codes != MAX_CODE;
}
