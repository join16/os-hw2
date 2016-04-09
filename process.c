#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *input, *output;

void mergeSort(unsigned int inputs[], int length);

void merge(unsigned int inputs[],
           unsigned int leftInputs[],
           unsigned int rightInputs[],
           int leftLength,
           int rightLength
);

void printArray(unsigned int arr[], int length) {
    for (int i = 0; i < length; i ++) {
        printf("%d\n", arr[i]);
    }
}

void swap(unsigned int *a, unsigned int *b) {
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {

    unsigned int inputs[10000];
    unsigned int value;
    int length = 0;
    size_t count;
    struct timespec before, after;

    input = fopen("./input", "rb");
    output = fopen("./process_output", "wb");

    while (!feof(input)) {
        count = fread(&value, 4, 1, input);

        if (count > 0) {
            inputs[length++] = value;
        }
    }

    mergeSort(inputs, length);

    for (int i = 0; i < length; i++) {
        fwrite(&inputs[i], 4, 1, output);
    }

    return 0;
}

// it returns length of handled array
void mergeSort(unsigned int inputs[], int length) {

    // for sort
    unsigned int *leftInputs, *rightInputs;

    // mid point index
    int leftLength, rightLength;

    // iteration index
    int i;
    int fdLeft[2], fdRight[2];
    int totalProcess;

    pid_t p1, p2;

    if ((length == 2) && (inputs[0] > inputs[1])) {
        swap(&inputs[0], &inputs[1]);
    }
    if (length <= 2) {
        return;
    }

    // split

    leftLength = length / 2;
    rightLength = length - leftLength;

    // forks

    pipe(fdLeft);
    pipe(fdRight);

    p1 = fork();

    if (p1 == 0) {
        // left child
        leftInputs = malloc(leftLength * sizeof(unsigned int));
        for (i = 0; i < leftLength; i++) {
            leftInputs[i] = inputs[i];
        }

        mergeSort(leftInputs, leftLength);
        // send
        write(fdLeft[1], leftInputs, leftLength * sizeof(unsigned int));
        free(leftInputs);
        exit(0);

    } else {
        p2 = fork();

        if (p2 == 0) {
            rightInputs = malloc(rightLength * sizeof(unsigned int));
            // right child
            for (i = leftLength; i < length; i++) {
                rightInputs[i - leftLength] = inputs[i];
            }
            mergeSort(rightInputs, rightLength);
            // send
            write(fdRight[1], rightInputs, rightLength * sizeof(unsigned int));
            free(rightInputs);
            exit(0);

        } else {
            leftInputs = malloc(leftLength * sizeof(unsigned int));
            rightInputs = malloc(rightLength * sizeof(unsigned int));
        };
    }

    // merge
    read(fdLeft[0], leftInputs, leftLength * sizeof(unsigned int));
    read(fdRight[0], rightInputs, rightLength * sizeof(unsigned int));

    merge(inputs, leftInputs, rightInputs, leftLength, rightLength);

    close(fdLeft[0]);
    close(fdRight[0]);
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