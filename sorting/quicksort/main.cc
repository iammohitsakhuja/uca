#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "pivots.hh"
#include "quicksort.hh"
#include "randomize_array.hh"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

using namespace std;

// Comparator declarations.
int integer_comparator(const void *a, const void *b);
int char_comparator(const void *a, const void *b);
int string_comparator(const void *a, const void *b);
int struct_comparator(const void *a, const void *b);

// Test prototypes.
void test_all(void);
void test_integers(int (*choose_pivot)(
    const void *, size_t, size_t, int (*)(const void *, const void *)));
void test_chars(int (*choose_pivot)(
    const void *, size_t, size_t, int (*)(const void *, const void *)));
void test_strings(int (*choose_pivot)(
    const void *, size_t, size_t, int (*)(const void *, const void *)));
void test_structures(int (*choose_pivot)(
    const void *, size_t, size_t, int (*)(const void *, const void *)));

// Test whether an array is sorted according to the comparator
// provided.
void test_array_is_sorted(const void *array, size_t nel, size_t width,
    int (*comparator)(const void *, const void *));

int main(void)
{
    test_all();
    printf("All tests passed!\n");
    return 0;
}

void test_all(void)
{
    // Seed for generating random numbers.
    srand(time(NULL));

    const int SIZE = 4;
    int (*choose_pivot[SIZE])(
        const void *, size_t, size_t, int (*)(const void *, const void *))
        = { choose_first_element_as_pivot, choose_last_element_as_pivot,
              choose_median_as_pivot, choose_random_pivot };

    for (int i = 0; i < SIZE; i++)
        test_integers(choose_pivot[i]);
    printf("Integer array tests passed with all ways of choosing a pivot\n");

    for (int i = 0; i < SIZE; i++)
        test_chars(choose_pivot[i]);
    printf("Character array tests passed with all ways of choosing a pivot\n");

    for (int i = 0; i < SIZE; i++)
        test_strings(choose_pivot[i]);
    printf("String array tests passed with all ways of choosing a pivot\n");

    for (int i = 0; i < SIZE; i++)
        test_structures(choose_pivot[i]);
    printf("Structure array tests passed with all ways of choosing a pivot\n");
}

void test_integers(int (*choose_pivot)(
    const void *, size_t, size_t, int (*)(const void *, const void *)))
{
    // Setup.
    const int SIZE = 10000;
    int *array     = (int *)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; i++)
        array[i] = rand() % SIZE;

    // Test.
    quicksort(array, SIZE, sizeof(int), integer_comparator, choose_pivot);
    test_array_is_sorted(array, SIZE, sizeof(int), integer_comparator);

    // Cleanup.
    free(array);
}

void test_chars(int (*choose_pivot)(
    const void *, size_t, size_t, int (*)(const void *, const void *)))
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
    quicksort(characters, SIZE, sizeof(char), char_comparator, choose_pivot);
    test_array_is_sorted(characters, SIZE, sizeof(char), char_comparator);

    // Cleanup.
    free(characters);
}

void test_strings(int (*choose_pivot)(
    const void *, size_t, size_t, int (*)(const void *, const void *)))
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
    quicksort(array, SIZE, sizeof(char *), string_comparator, choose_pivot);
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

void test_structures(int (*choose_pivot)(
    const void *, size_t, size_t, int (*)(const void *, const void *)))
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
    quicksort(array, SIZE, sizeof(TS), struct_comparator, choose_pivot);
    test_array_is_sorted(array, SIZE, sizeof(TS), struct_comparator);

    // Cleanup.
    free(array);
}

// For testing whether an array is sorted.
void test_array_is_sorted(const void *array, size_t nel, size_t width,
    int (*comparator)(const void *, const void *))
{
    const char *arr = (const char *)array;
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
