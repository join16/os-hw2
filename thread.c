#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

FILE *input, *output;

typedef struct {
    unsigned int *inputs;
    int length;
} threadData;

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

void mergeSortInThread(threadData *_data);

int main() {

    unsigned int inputs[10000];
    unsigned int value;
    int length = 0;
    size_t count;

    input = fopen("./input", "rb");
    output = fopen("./thread_output", "wb");

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

    // thread related
    threadData leftData, rightData;
    pthread_t leftThread, rightThread;

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

    leftInputs = malloc(leftLength * sizeof(unsigned int));
    rightInputs = malloc(rightLength * sizeof(unsigned int));

    for (i = 0; i < leftLength; i++) {
        leftInputs[i] = inputs[i];
    }

    for (i = leftLength; i < length; i++) {
        rightInputs[i - leftLength] = inputs[i];
    }

    leftData.inputs = leftInputs;
    leftData.length = leftLength;

    rightData.inputs = rightInputs;
    rightData.length = rightLength;

    // executes thread
    pthread_create(&leftThread, NULL, (void *) &mergeSortInThread, (void *) &leftData);
    pthread_create(&rightThread, NULL, (void *) &mergeSortInThread, (void *) &rightData);

    // merge
    pthread_join(leftThread, NULL);
    pthread_join(rightThread, NULL);

    merge(inputs, leftInputs, rightInputs, leftLength, rightLength);

    free(leftInputs);
    free(rightInputs);
}

void mergeSortInThread(threadData *_data) {
    threadData data = *_data;
    mergeSort(data.inputs, data.length);
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