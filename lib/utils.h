#ifndef HW2_UTILS_H
#define HW2_UTILS_H

#include <time.h>

long getTimeDiff(struct timespec *start, struct timespec *end);

// makes nanosecond value into second
double toSecond(long ns);

#endif //HW2_UTILS_H