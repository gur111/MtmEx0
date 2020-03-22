#include "part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

inline int readInputSize(void) {
    int size = 0;
    printf("Enter size of input:\n");
    scanf("%d", &size); // NOLINT(cert-err34-c)

    if (size <= 0) {
        printf("Invalid size\n");
        exit(1);
    }

    return size;
}

inline int readNumber(long *result) {
    long num;
    char buff[MAX_LONG_AS_STR_SIZE], *endptr;

    scanf("%s", buff);

    num = strtol(buff, &endptr, 10);

    if (buff == endptr || *endptr != '\0') {
        printf("Invalid number\n");
        return -1;
    }

    *result = num;
    return 0;
}


int main(void) {
    int count = readInputSize();
    int sum = 0, *logs = calloc(count, sizeof(int)), logIndex = 0;
    double logRes;
    long num;

    printf("Enter numbers:\n");

    for (int i = 0; i < count; i++) {
        if (!readNumber(&num)){
            free(logs);
            exit(1);
        }
        pow(10, 4);
        logRes = (double) log2l(num);
        if ((double) logRes == (int) logRes) {
            sum += (int) logRes;
            logs[logIndex++] = (int) logRes;
        }

    }

    for (int i = 0; i < logIndex; i++) {
        num = (long) powl(2, logs[i]);

        printf("The number %ld is a power of 2: %ld = 2^%d\n", num, num, logs[i]);
    }

    printf("Total exponent sum is %d\n", sum);

    free(logs);

    return 0;
}