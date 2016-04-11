
#include <stdio.h>
#include <stdlib.h>

#include "file_handler.h"

int readArrayFromInputFile(const char *fileName, unsigned int *inputs) {

    FILE *input;
    size_t count;
    unsigned int value;
    int length = 0;

    input = fopen(fileName, "rb");

    if (input == NULL) {
        printf("Input file not found!\n");
        exit(1);
    }

    while (!feof(input)) {
        count = fread(&value, 4, 1, input);

        if (count > 0) {
            inputs[length++] = value;
        }
    }

    if (length == 0) {
        printf("Empty Input File!\n");
        exit(0);
    }

    fclose(input);

    return length;
}

void writeIntoOutputFile(const char *fileName, unsigned int *outputs, int length) {

    FILE *output;

    // for iteration
    int i;

    output = fopen(fileName, "wb");

    for (i = 0; i < length; i++) {
        fwrite(&outputs[i], 4, 1, output);
    }

    fclose(output);
}