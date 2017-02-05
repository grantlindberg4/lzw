#ifndef BITS_H
#define BITS_H

#include <stdio.h>
#include <stdbool.h>

_Bool read_code(FILE* input, unsigned int* code);
void write_code(FILE* output, unsigned int code);

#endif
