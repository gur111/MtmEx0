#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

// Convert to string
#define STR_HELPER(x) #x
#define STRING(x) STR_HELPER(x)

// This is because the int max size is 19 digits + sign + \0
#define MAX_LONG_AS_STRING_SIZE 21
#define INVALID (-1)

/* Reads a number to be used as input size */
int readInputSize(void);

/* Reads a number from the user */
bool readNumber(long *result);

/* Simplified implementation of simpleLog2
 * Returns an integer, returns INVALID if the result is not an integer */
int simpleLog2(long number);

/*
 * Calculates and returns the value of 2^exponent
 */
long pow2(int exponent);


int simpleLog2(long number) {
    int count = 0;
    if (number <= 0) {
        return INVALID;
    }

    while (number != 1) {
        if (number % 2 != 0) {
            return INVALID;
        }
        count++;
        number = number / 2;
    }

    return count;
}

long pow2(int exponent) {
    if (exponent >= 62) {
        printf("The value would be too big");
        return INVALID;
    }
    long result = 1;
    for (int i = 0; i < exponent; i++, result *= 2);

    return result;
}

int readInputSize(void) {
    long size;
    printf("Enter size of input:\n");

    if (!readNumber(&size) || size < 1 || (int) size != size) {
        printf("Invalid size\n");
        exit(0);
    }

    return (int) size;
}

bool readNumber(long *result) {
    long number;
    // To be able to occupy an extra char so we can detect overflow in buffer
    char buffer[MAX_LONG_AS_STRING_SIZE + 1], *endptr;

    scanf("%"STRING(MAX_LONG_AS_STRING_SIZE)"s", buffer);

    errno = 0;
    number = strtol(buffer, &endptr, 10);

    if (buffer == endptr || *endptr != '\0' || errno != 0) {
        return false;
    }

    *result = number;
    return true;
}


int main(void) {
    int count = readInputSize();
    int exponent_summation = 0;
    int *logs_results = malloc(count * sizeof(int));
    int log_index = 0;
    int current_log_res;
    long current_number;

    if (!logs_results) {
        printf("Failed to allocate memory");
        return 0;
    }

    printf("Enter numbers:\n");

    // Loops through inputs, save the relevant input's log2 results
    for (int i = 0; i < count; i++) {
        if (!readNumber(&current_number)) {
            printf("Invalid number\n");
            free(logs_results);
            return 0;
        }

        current_log_res = simpleLog2(current_number);
        if (current_log_res != INVALID) {
            exponent_summation += (int) current_log_res;
            logs_results[log_index++] = (int) current_log_res;
        }

    }

    // Print the results in a pretty format
    for (int i = 0; i < log_index; i++) {
        current_number = pow2(logs_results[i]);
        printf("The number %ld is a power of 2: %ld = 2^%d\n",
               current_number, current_number, logs_results[i]);
    }

    printf("Total exponent sum is %d\n", exponent_summation);
    free(logs_results);

    return 0;
}