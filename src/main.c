#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "lzw.h"
#include "seq.h"

// Tests to be run:
// check all functions in sequence - OK!
// try freeing sequences and check for mem leaks in valgrind
// check input parsing
// initialize dictionary correctly (examine contents) (make array smaller)
// add one entry to dictionary
// Don't forget to figure out how to output last sequence in decode()
// How to do debugging for program?

void display_usage_message() {
    fprintf(stderr, "Usage:  ./lzw <option1> <option2> ... <optionN>\n");
    fprintf(stderr, "        Where <option>'s must be one or more of the following:\n");
    fprintf(stderr, "-help               print this message\n");
    fprintf(stderr, "-encode             compress input\n");
    fprintf(stderr, "-decode             expand compressed input\n");
    fprintf(stderr, "-input <pathname>   read data from file (stdin by default)\n");
    fprintf(stderr, "-output <pathname>  write output to file (stdout by default)\n\n");
}

enum CompressionType {
    None,
    Encode,
    Decode,
};

enum FileType {
    Nil,
    Input,
    Output,
};

int main(int argc, char** argv) {
    FILE* input_type = stdin;
    FILE* output_type = stdout;

    enum CompressionType compression = None;
    enum FileType file_type = Nil;

    _Bool able_to_execute = true;
    _Bool searching_for_file = false;

    _Bool checked_for_input = false;
    _Bool checked_for_output = false;

    if(argc == 1) {
        fprintf(stderr, "Warning: Nothing to do. Specify either -encode or -decode\n\n");
        display_usage_message();
        return 0;
    }

    for(int i = 1; i < argc; i++) {
        if(!able_to_execute) {
            break;
        }
        if(strcmp(argv[i] ,"-help") == 0) {
            able_to_execute = false;
        }
        else if(strcmp(argv[i], "-encode") == 0) {
            if(searching_for_file || compression != None) {
                able_to_execute = false;
            }
            compression = Encode;
        }
        else if(strcmp(argv[i], "-decode") == 0) {
            if(searching_for_file || compression != None) {
                able_to_execute = false;
            }
            compression = Decode;
        }
        else if(strcmp(argv[i], "-input") == 0) {
            if(searching_for_file || checked_for_input) {
                able_to_execute = false;
            }
            searching_for_file = true;
            checked_for_input = true;
            file_type = Input;
        }
        else if(strcmp(argv[i], "-output") == 0) {
            if(searching_for_file || checked_for_output) {
                able_to_execute = false;
            }
            searching_for_file = true;
            checked_for_output = true;
            file_type = Output;
        }
        else {
            if(searching_for_file) {
                if(file_type == Input) {
                    input_type = fopen(argv[i], "r");
                    if(input_type == NULL) {
                        fprintf(stderr, "Could not find the specified file\n\n");
                        able_to_execute = false;
                    }
                    file_type = Nil;
                }
                else if(file_type == Output) {
                    output_type = fopen(argv[i], "w");
                    if(output_type == NULL) {
                        fprintf(stderr, "Could not find the specified file\n\n");
                        able_to_execute = false;
                    }
                    file_type = Nil;
                }
                searching_for_file = false;
            }
            else {
                able_to_execute = false;
            }
        }
    }

    if(able_to_execute) {
        if(compression == Encode) {
            encode(input_type, output_type);
            fflush(output_type);
        }
        else if(compression == Decode) {
            decode(input_type, output_type);
            fflush(output_type);
        }
        else {
            perror("Please specify a compression type\n\n");
            display_usage_message();
        }
    }
    else {
        display_usage_message();
    }

    return 0;
}
