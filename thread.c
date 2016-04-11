
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

#include "lib/merge_sort.h"
#include "lib/file_handler.h"
#include "lib/utils.h"

#define OUTPUT_FILE "./thread_output"

typedef struct {
    unsigned int *inputs;
    int length;
    struct timespec start, end;
} threadData;

int totalThreadCount = 0;
long totalCreateTime = 0;

// function declarations
void mergeSortInThread(threadData *data);
void childExecution(unsigned int *inputs, int length);

int main(const int argc, const char *argv[]) {

    const char *inputFileName = argv[1];
    unsigned int inputs[10000];
    int length;

    struct timespec start, end;

    long totalExecutionTime = 0;

    // start counting execution time
    clock_gettime(CLOCK_MONOTONIC, &start);

    length = readArrayFromInputFile(inputFileName, inputs);

    mergeSort(inputs, length, childExecution);

    writeIntoOutputFile(OUTPUT_FILE, inputs, length);

    // end counting
    clock_gettime(CLOCK_MONOTONIC, &end);

    totalExecutionTime = getTimeDiff(&start, &end);

    printf("Total execution time:\t%.9f\n", toSecond(totalExecutionTime));
    printf("Total process count: %d, Average pthread_create() time: %ld\n",
           totalThreadCount,
           (totalCreateTime / totalThreadCount)
    );

    return 0;
}

void childExecution(unsigned int *leftInputs, int leftLength) {
    threadData data = {leftInputs, leftLength};
    pthread_t thread;

    // start counting thread creation time
    clock_gettime(CLOCK_MONOTONIC, &data.start);

    pthread_create(&thread, NULL, (void *) &mergeSortInThread, (void *) &data);
    pthread_join(thread, NULL);
}

void mergeSortInThread(threadData *data) {

    // end counting thread creation time
    clock_gettime(CLOCK_MONOTONIC, &(data->end));

    // add +1 to total thread count
    totalThreadCount++;

    // add thread creation time to global variable
    totalCreateTime += getTimeDiff(&(data->start), &(data->end));

    mergeSort(data->inputs, data->length, childExecution);
}