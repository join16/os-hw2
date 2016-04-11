
#ifndef HW2_MERGE_SORT_H
#define HW2_MERGE_SORT_H

#include <stdio.h>
#include <stdlib.h>

void mergeSort(unsigned int *inputs,
               int length,
               void (*childExecution)(unsigned int *leftInputs, int leftLength)
);


void merge(unsigned int inputs[],
           unsigned int leftInputs[],
           unsigned int rightInputs[],
           int leftLength,
           int rightLength
);

#endif //HW2_MERGE_SORT_H
