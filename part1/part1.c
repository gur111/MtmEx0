#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LONG_AS_STR_SIZE 21 // This is because the int max size is 19 digits + sign + \0
#define INVALID (-1)

/* Reads a number to be used as input size */
int readInputSize(void);

/* Reads a number from the user */
bool readNumber(long *result);

/* Simplified implementation of simpleLog2
 * Returns an integer, returns INVALID if the result is not an integer */
int simpleLog2(long num);

/*
 * Calculates and returns the value of 2^exp
 */
long pow2(int exp);


int simpleLog2(long num) {
    int count = 0;
    if (num <= 0) {
        return INVALID;
    }

    while (num != 1) {
        if (num % 2 != 0) {
            return INVALID;
        }
        count++;
        num = num / 2;
    }

    return count;
}

long pow2(int exp){
    if (exp >= 62){
        printf("The value would be too big");
        return INVALID;
    }
    long res = 1;
    for(int i= 0; i<exp; i++, res*=2);

    return res;
}

int readInputSize(void) {
    int size = 0;
    printf("Enter size of input:\n");
    scanf("%d", &size); // NOLINT(cert-err34-c)

    if (size <= 0) {
        printf("Invalid size\n");
        exit(0);
    }

    return size;
}

bool readNumber(long *result) {
    long num;
    char buff[MAX_LONG_AS_STR_SIZE], *endptr;

    scanf("%s", buff);

    num = strtol(buff, &endptr, 10);

    if (buff == endptr || *endptr != '\0') {
        printf("Invalid number\n");
        return false;
    }

    *result = num;
    return true;
}


int main(void) {
    int count = readInputSize();
    int sum = 0, *logs = malloc(count * sizeof(int)), logIndex = 0;
    int logRes;
    long num;

    if (!logs){
        printf("Failed to allocate memory");
        return 0;
    }

    printf("Enter numbers:\n");

    for (int i = 0; i < count; i++) {
        if (!readNumber(&num)) {
            free(logs);
            return 0;
        }

        logRes = simpleLog2(num);
        if (logRes != INVALID) {
            sum += (int) logRes;
            logs[logIndex++] = (int) logRes;
        }

    }

    for (int i = 0; i < logIndex; i++) {
        num = pow2(logs[i]);

        printf("The number %ld is a power of 2: %ld = 2^%d\n", num, num, logs[i]);
    }

    printf("Total exponent sum is %d\n", sum);
    free(logs);

    return 0;
}