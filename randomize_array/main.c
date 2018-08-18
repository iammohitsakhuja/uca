#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "randomize_array.h"

void test(void);

int main(void)
{
    test();
    return 0;
}

void test_integers(void)
{
    // Setup.
    const int SIZE = 10;
    int *array     = (int *)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++)
        array[i] = i;

    // Randomize the array.
    randomize_array(array, SIZE, sizeof(int));

    // Test.
    bool array_is_randomized = false;
    for (int i = 0; i < SIZE; i++)
        if (array[i] != i) {
            array_is_randomized = true;
            break;
        }
    assert(array_is_randomized);

    // Cleanup.
    free(array);
}

void test_chars(void)
{
    // Setup.
    const int SIZE = 26;
    char *array    = (char *)malloc(SIZE * sizeof(char));
    for (int i = 0; i < SIZE; i++)
        array[i] = 65 + i;

    // Randomize the array.
    randomize_array(array, SIZE, sizeof(char));

    // Test.
    bool array_is_randomized = false;
    for (int i = 0; i < SIZE; i++)
        if (array[i] != 65 + i) {
            array_is_randomized = true;
            break;
        }
    assert(array_is_randomized);

    // Cleanup.
    free(array);
}

void test_strings(void)
{
    // Setup.
    const int SIZE          = 10;
    const int LENGTH        = 4;
    const char strings[][6] = { "ABC", "DEF", "GHI", "JKL", "MNO", "PQR",
        "STU", "VXW", "YZA", "BCD" };

    char **array = (char **)malloc(SIZE * sizeof(char *));
    for (int i = 0; i < SIZE; i++) {
        array[i] = (char *)malloc(LENGTH * sizeof(char));
        strcpy(array[i], strings[i]);
    }

    // Randomize the array.
    randomize_array(array, SIZE, sizeof(char *));

    // Test.
    bool array_is_randomized = false;
    for (int i = 0; i < SIZE; i++)
        if (strcmp(array[i], strings[i]) != 0) {
            array_is_randomized = true;
            break;
        }
    assert(array_is_randomized);

    // Cleanup.
    for (int i = 0; i < SIZE; i++)
        free(array[i]);
    free(array);
}

void test_structures(void)
{
    // Setup.
    typedef struct test_structure {
        int num1;
        int num2;
    } TS;

    const int SIZE = 10;
    TS *array      = (TS *)malloc(SIZE * sizeof(TS));
    for (int i = 0; i < SIZE; i++) {
        array[i].num1 = i;
        array[i].num2 = SIZE - i;
    }

    // Randomize the array.
    randomize_array(array, SIZE, sizeof(TS));

    // Test.
    bool array_is_randomized = false;
    for (int i = 0; i < SIZE; i++) {
        if (array[i].num1 != i && array[i].num2 == SIZE - array[i].num1) {
            array_is_randomized = true;
            break;
        }
    }
    assert(array_is_randomized);

    // Cleanup.
    free(array);
}

void test(void)
{
    test_integers();
    printf("Integer array tests passed!\n");

    test_chars();
    printf("Character array tests passed!\n");

    test_strings();
    printf("String array tests passed!\n");

    test_structures();
    printf("Structure array tests passed!\n");

    printf("\nAll tests passed!\n");
}
