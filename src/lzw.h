#ifndef LZW_H
#define LZW_H

#include <stdio.h>

void encode(FILE* input, FILE* output);
void decode(FILE* input, FILE* output);

#endif
