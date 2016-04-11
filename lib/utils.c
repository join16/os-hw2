
#include <time.h>

#include "utils.h"

const int BILLION = 1000000000;

long getTimeDiff(struct timespec *start, struct timespec *end) {
    long secDiff = end->tv_sec - start->tv_sec;
    long nsDiff = end->tv_nsec - start->tv_nsec;

    return (secDiff * BILLION) + nsDiff;
}

// makes nanosecond value into second
double toSecond(long ns) {
    return ns / (double) BILLION;
}

