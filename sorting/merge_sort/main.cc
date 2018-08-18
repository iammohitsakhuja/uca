#include "merge_sort.hh"
#include "randomize_array.hh"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

// Comparator declarations.
int integer_comparator(const void *a, const void *b);
int char_comparator(const void *a, const void *b);
int string_comparator(const void *a, const void *b);
int struct_comparator(const void *a, const void *b);

// Test prototypes.
void test(void);
void test_integers(void);
void test_chars(void);
void test_strings(void);
void test_structures(void);

// Test whether an array is sorted according to the comparator provided.
void test_array_is_sorted(void *array, size_t nel, size_t width,
    int (*comparator)(const void *a, const void *b));

int main(void)
{
    test();
    printf("All tests passed!\n");
    return 0;
}

void test(void)
{
    // Seed for generating random numbers.
    srand(time(NULL));

    // Test merge sort with integers.
    test_integers();
    printf("Integer array tests passed!\n");

    // Test merge sort with characters.
    test_chars();
    printf("Character array tests passed!\n");

    // Test merge sort with strings.
    test_strings();
    printf("String array tests passed!\n");

    // Test merge sort with structure.
    test_structures();
    printf("Structure array tests passed!\n");
}

void test_integers(void)
{
    // Setup.
    const int SIZE = 10000;
    int *array     = (int *)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % SIZE;

    // Test.
    merge_sort(array, SIZE, sizeof(int), integer_comparator);
    test_array_is_sorted(array, SIZE, sizeof(int), integer_comparator);

    // Cleanup.
    free(array);
}

void test_chars(void)
{
    // Setup.
    const int SIZE   = 52;
    char *characters = (char *)malloc(SIZE * sizeof(char));
    for (int i = 0; i < SIZE / 2; i++) {
        characters[i]            = 65 + i;
        characters[SIZE / 2 + i] = 97 + i;
    }

    // Randomize the characters before sorting.
    randomize_array(characters, SIZE, sizeof(char));

    // Sort and test.
    merge_sort(characters, SIZE, sizeof(char), char_comparator);
    test_array_is_sorted(characters, SIZE, sizeof(char), char_comparator);

    // Cleanup.
    free(characters);
}

void test_strings(void)
{
    // Setup.
    const int SIZE                   = 10;
    const int LENGTH                 = 4;
    const char strings[SIZE][LENGTH] = { "ABC", "DEF", "GHI", "JKL", "MNO",
        "PQR", "STU", "VWX", "YZA", "BCD" };
    char **array                     = (char **)malloc(SIZE * sizeof(char *));
    for (int i = 0; i < SIZE; i++) {
        array[i] = (char *)malloc(LENGTH * sizeof(char));
        strcpy(array[i], strings[i]);
    }

    // Randomize the strings before sorting.
    randomize_array(array, SIZE, sizeof(char *));

    // Sort and test.
    merge_sort(array, SIZE, sizeof(char *), string_comparator);
    test_array_is_sorted(array, SIZE, sizeof(char *), string_comparator);

    // Cleanup.
    for (int i = 0; i < SIZE; i++)
        free(array[i]);
    free(array);
}

typedef struct test_structure {
    int num1;
    int num2;
} TS;

void test_structures(void)
{
    // Setup.
    const int SIZE = 10;
    TS *array      = (TS *)malloc(SIZE * sizeof(TS));
    for (int i = 0; i < SIZE; i++) {
        array[i].num1 = i;
        array[i].num2 = SIZE - i;
    }

    // Randomize.
    randomize_array(array, SIZE, sizeof(TS));

    // Sort and test.
    merge_sort(array, SIZE, sizeof(TS), struct_comparator);
    test_array_is_sorted(array, SIZE, sizeof(TS), struct_comparator);

    // Cleanup.
    free(array);
}

void test_array_is_sorted(void *array, size_t nel, size_t width,
    int (*comparator)(const void *a, const void *b))
{
    char *arr = (char *)array;
    for (int i = 0, size = nel - 1; i < size; i++)
        assert(comparator(arr + i * width, arr + (i + 1) * width) <= 0);
}

// Comparators.
int integer_comparator(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

int char_comparator(const void *a, const void *b)
{
    return *(const char *)a - *(const char *)b;
}

int string_comparator(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int struct_comparator(const void *a, const void *b)
{
    return (*(const TS *)a).num1 - (*(const TS *)b).num1;
}
