#include "seq.h"
#include "table.h"

Table* create_table() {
    Table* code_table = malloc(sizeof(Table));
    code_table->size = MAX_CODE;
    code_table->array = (Sequence**)calloc(code_table->size, sizeof(Sequence*));

    return code_table;
}

Table* initialize_table() {
    Table* code_table = create_table();
    for(int i = 0; i < NUM_CHARS; i++) {
        char c = i;
        Sequence* sequence = create_sequence();
        append(sequence, c);
        code_table->array[i] = sequence;
    }

    return code_table;
}

void destroy_table(Table* code_table) {
    for(int i = 0; i < MAX_CODE; i++) {
        if(code_table->array[i] != NULL) {
            delete_sequence(code_table->array[i]);
        }
    }
    free(code_table->array);
    free(code_table);
}

_Bool code_exists_in_table(Table* code_table, unsigned int code) {
    return code_table->array[code] != NULL;
}

int table_is_full(Table* code_table) {
    for(int i = 0; i < MAX_CODE; i++) {
        if(code_table->array[i] == NULL) {
            return i;
        }
    }

    return -1;
}
