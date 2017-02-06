#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "lzw.h"
#include "dict.h"
#include "bits.h"
#include "seq.h"
#include "table.h"

void encode(FILE* input, FILE* output) {
    Dict* dictionary = initialize_dictionary();

    int next_code = NUM_CHARS;
    int c = fgetc(input);
    Sequence* W = create_sequence();
    if(c != EOF) {
        append(W, c);
    }
    while(c != EOF) {

        c = fgetc(input);
        if(c == EOF) {
            break;
        }
        Sequence* X = copy_sequence(W);
        append(X, c);
        unsigned int code;
        bool found_code = search_for_key(dictionary, X, &code);
        if(found_code) {
            delete_sequence(W);
            W = copy_sequence(X);
        }
        else {
            found_code = search_for_key(dictionary, W, &code);
            assert(found_code);
            write_code(output, code);
            if(space_in(dictionary, next_code)) {
                insert_to_dictionary(dictionary, copy_sequence(X), next_code);
                next_code++;
            }
            delete_sequence(W);
            W = create_sequence();
            append(W, c);
        }
        delete_sequence(X);
    }
    unsigned int code;
    bool found_code = search_for_key(dictionary, W, &code);
    if(found_code) {
        write_code(output, code);
    }

    delete_sequence(W);
    destroy_dictionary(dictionary);
}

void decode(FILE* input, FILE* output) {
    Table* code_table = initialize_table();

    unsigned int prev_code;
    bool reading_codes = read_code(input, &prev_code);
    if(reading_codes && code_exists_in_table(code_table, prev_code)) {
        output_sequence(code_table->array[prev_code], output);
    }
    while(reading_codes) {
        unsigned int curr_code;
        reading_codes = read_code(input, &curr_code);
        if(!reading_codes) {
            break;
        }
        char c;
        if(code_exists_in_table(code_table, curr_code)) {
            c = first_char_of(code_table->array[curr_code]);
        }
        else {
            assert(code_exists_in_table(code_table, prev_code));
            c = first_char_of(code_table->array[prev_code]);
        }
        int i = table_is_full(code_table);
        if(i >= 0) {
            Sequence* W = copy_sequence(code_table->array[prev_code]);
            append(W, c);
            code_table->array[i] = W;
        }
        output_sequence(code_table->array[curr_code], output);
        prev_code = curr_code;
    }

    destroy_table(code_table);
}
