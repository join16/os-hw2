#include <stdio.h>
#include <stdlib.h>

FILE *input, *output;

int main() {
    unsigned int inputs[10000];
    unsigned int value;
    int length = 0;
    int i;
    size_t count;

    input = fopen("./process_output", "rb");

    while (!feof(input)) {
        count = fread(&value, 4, 1, input);

        if (count > 0) {
            inputs[length++] = value;
        }
    }

    for (i = 0; i < length; i++) {
        printf("%d\n", inputs[i]);
    }
}