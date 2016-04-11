#ifndef HW2_FILE_HANDLER_H
#define HW2_FILE_HANDLER_H

// returns length of array
int readArrayFromInputFile(const char *fileName, unsigned int *inputs);

void writeIntoOutputFile(const char *fileName, unsigned int *outputs, int length);

#endif //HW2_FILE_HANDLER_H
