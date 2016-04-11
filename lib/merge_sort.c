
#include <stdio.h>
#include <stdlib.h>

#include "merge_sort.h"

void mergeSort(unsigned int *inputs,
               int length,
               void (*childExecution)(unsigned int *inputs, int length)
) {

    // variables for split arrays
    unsigned int *leftInputs, *rightInputs;
    int leftLength, rightLength;

    // for iteration
    int i;

    // if length < 2, return
    if (length < 2) {
        return;
    }


    // split length
    leftLength = length / 2;
    rightLength = length - leftLength;

    // split arrays
    leftInputs = malloc(leftLength * sizeof(unsigned int));
    rightInputs = malloc(rightLength * sizeof(unsigned int));

    for (i = 0; i < leftLength; i++) {
        leftInputs[i] = inputs[i];
    }

    for (i = leftLength; i < length; i++) {
        rightInputs[i - leftLength] = inputs[i];
    }

    // left child execution
    childExecution(leftInputs, leftLength);

    // right child execution
    childExecution(rightInputs, rightLength);

    // merge execution
    merge(inputs, leftInputs, rightInputs, leftLength, rightLength);

    // free dynamically allocated memory
    free(leftInputs);
    free(rightInputs);
}

void merge(unsigned int inputs[],
           unsigned int leftInputs[],
           unsigned int rightInputs[],
           int leftLength,
           int rightLength
) {

    // for iteration
    int i = 0, j = 0, k = 0;

    while ((i < leftLength) && (j < rightLength)) {
        inputs[k++] = (leftInputs[i] < rightInputs[j]) ?
                      leftInputs[i++] :
                      rightInputs[j++];
    }

    while (i < leftLength) {
        inputs[k++] = leftInputs[i++];
    }
    while (j < rightLength) {
        inputs[k++] = rightInputs[j++];
    }
}