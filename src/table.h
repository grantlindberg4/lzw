#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>

#include "dict.h"
#include "seq.h"

typedef struct Table {
	int size;
	Sequence** array;
} Table;

Table* initialize_table();
Table* create_table();
void destroy_table(Table* code_table);
_Bool code_exists_in_table(Table* code_table, unsigned int code);
int table_is_full(Table* code_table);

#endif
