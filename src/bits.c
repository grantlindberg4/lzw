#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "bits.h"

bool read_code(FILE* input, unsigned int* code) {
    int msb = fgetc(input);
    if(msb == EOF) {
        return false;
    }
    int lsb = fgetc(input);
    if(lsb == EOF) {
        return false;
    }
    unsigned int result = ((msb & 0xFF) << 8) | (lsb & 0xFF);
    *code = result;

    return true;
}

void write_code(FILE* output, unsigned int code) {
    char msb = (code >> 8) & 0xFF;
    char lsb = code & 0xFF;
    fputc(msb, output);
    fputc(lsb, output);
}
