#include <stdio.h>
#include <stdlib.h>

FILE *input, *output;

void mergeSort(unsigned int inputs[], int length);

void merge(unsigned int inputs[],
           unsigned int leftInputs[],
           unsigned int rightInputs[],
           int leftLength,
           int rightLength
);

int main() {

    unsigned int inputs[10000];
    unsigned int value;
    int length = 0;
    size_t count;

    input = fopen("./input", "rb");

    while (!feof(input)) {
        count = fread(&value, 4, 1, input);

        if (count > 0) {
            inputs[length++] = value;
        }
    }

    printf("Before sorts...\n");
    for (int i = 0; i < length; i++) {
        printf("%d\n", inputs[i]);
    }

    // split
    mergeSort(inputs, length);

    printf("After sorts...\n");

    for (int i = 0; i < length; i++) {
        printf("%d\n", inputs[i]);
    }

    return 0;
}

void mergeSort(unsigned int inputs[], int length) {

    // for sort
    unsigned int *leftInputs, *rightInputs;

    // mid point index
    int leftLength, rightLength;

    // iteration index
    int i;

    if (length < 2) {
        return;
    }

    // split

    leftLength = length / 2;
    rightLength = length - leftLength;

    leftInputs = malloc(leftLength * sizeof(unsigned int));
    rightInputs = malloc(rightLength * sizeof(unsigned int));

    for (i = 0; i < leftLength; i++) {
        leftInputs[i] = inputs[i];
    }
    for (i = leftLength; i < length; i++) {
        rightInputs[i - leftLength] = inputs[i];
    }

    // sorts
    mergeSort(leftInputs, leftLength);
    mergeSort(rightInputs, rightLength);

    // merge
    merge(inputs, leftInputs, rightInputs, leftLength, rightLength);
    free(leftInputs);
    free(rightInputs);
}

void merge(unsigned int inputs[],
           unsigned int leftInputs[],
           unsigned int rightInputs[],
           int leftLength,
           int rightLength
) {
    int i = 0;
    int j = 0;
    int k = 0;

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