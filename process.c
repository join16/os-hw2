
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include "lib/merge_sort.h"
#include "lib/file_handler.h"
#include "lib/utils.h"

#define OUTPUT_FILE "./process_output"

int totalProcessCount = 0;
long totalForkTime = 0;

void childExecution(unsigned int *inputs, int length);

int main(const int argc, const char *argv[]) {

    const char *inputFileName = argv[1];
    unsigned int inputs[10000];
    int length;

    struct timespec start, end;

    long totalExecutionTime;

    // start counting
    clock_gettime(CLOCK_MONOTONIC, &start);

    length = readArrayFromInputFile(inputFileName, inputs);

    mergeSort(inputs, length, childExecution);

    writeIntoOutputFile(OUTPUT_FILE, inputs, length);

    // end counting
    clock_gettime(CLOCK_MONOTONIC, &end);

    totalExecutionTime = getTimeDiff(&start, &end);

    printf("Total execution time:\t%.9f\n", toSecond(totalExecutionTime));
    printf("Total process count: %d, Average fork() time: %ld\n",
           totalProcessCount,
           (totalForkTime / totalProcessCount)
    );

    return 0;
}

void childExecution(unsigned int *leftInputs, int leftLength) {

    int fd[2];

    int processCountOfChild;
    long forkTimeOfChild;

    struct timespec start, end;

    pipe(fd);

    // start counting time
    clock_gettime(CLOCK_MONOTONIC, &start);

    pid_t p = fork();

    // end counting time
    clock_gettime(CLOCK_MONOTONIC, &end);

    if (p == 0) {
        // child process

        // child process cannot use fd[0] (read)
        close(fd[0]);

        // set process count, forkTime of child
        totalProcessCount = 1;
        totalForkTime = getTimeDiff(&start, &end);

        mergeSort(leftInputs, leftLength, childExecution);

        write(fd[1], leftInputs, leftLength * sizeof(unsigned int));
        write(fd[1], &totalProcessCount, sizeof(totalProcessCount));
        write(fd[1], &totalForkTime, sizeof(totalForkTime));

        close(fd[1]);

        free(leftInputs);

        exit(0);
    } else {

        // parent process cannot use fd[1] (write)
        close(fd[1]);

        read(fd[0], leftInputs, leftLength * sizeof(unsigned int));
        read(fd[0], &processCountOfChild, sizeof(processCountOfChild));
        read(fd[0], &forkTimeOfChild, sizeof(forkTimeOfChild));

        close(fd[0]);

        totalProcessCount += processCountOfChild;
        totalForkTime += forkTimeOfChild;
    }
}