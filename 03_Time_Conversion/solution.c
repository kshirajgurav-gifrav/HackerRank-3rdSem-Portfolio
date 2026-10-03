#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

char* timeConversion(char* s) {
    // Allocate 9 bytes for "HH:MM:SS" + null terminator '\0'
    char* result = malloc(9 * sizeof(char));

    // Extract the two-digit hour
    int hour = (s[0] - '0') * 10 + (s[1] - '0');

    // Convert hour based on AM or PM (located at index 8)
    if (s[8] == 'A') {
        if (hour == 12) {
            hour = 0;
        }
    } else if (s[8] == 'P') {
        if (hour != 12) {
            hour += 12;
        }
    }

    // Copy the first 8 characters ("HH:MM:SS") and null-terminate
    strncpy(result, s, 8);
    result[8] = '\0';

    // Update the first two characters with the converted 24-hour value
    result[0] = (hour / 10) + '0';
    result[1] = (hour % 10) + '0';

    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = timeConversion(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}