#include <cstdlib>
#include <cstring>

#include "quicksort.hh"

#define SWAP(a, b, aux, width)                                                \
    do {                                                                      \
        char *__a  = a;                                                       \
        char *__b  = b;                                                       \
        char *temp = (char *)aux;                                             \
        memcpy(temp, __a, width);                                             \
        memcpy(__a, __b, width);                                              \
        memcpy(__b, temp, width);                                             \
    } while (0);

static void qsort(void *array, void *aux, size_t nel, size_t width,
    int (*comparator)(const void *, const void *),
    int (*choose_pivot)(
        const void *, size_t, size_t, int (*)(const void *, const void *)));

static int partition(void *array, void *aux, size_t nel, size_t width,
    int (*comparator)(const void *, const void *));

void quicksort(void *array, size_t nel, size_t width,
    int (*comparator)(const void *, const void *),
    int (*choose_pivot)(
        const void *, size_t, size_t, int (*)(const void *, const void *)))
{
    // Create an auxiliary space once, in order to save repetitive malloc calls
    // made during swapping.
    void *aux = (void *)malloc(width);

    // Sort the array.
    qsort(array, aux, nel, width, comparator, choose_pivot);

    // Housekeeping.
    free(aux);
}

static void qsort(void *array, void *aux, size_t nel, size_t width,
    int (*comparator)(const void *, const void *),
    int (*choose_pivot)(
        const void *, size_t, size_t, int (*)(const void *, const void *)))
{
    // If there is only 1 element or less, then it is already sorted.
    if (nel <= 1)
        return;

    char *arr = (char *)array;

    // Choose a pivot by using the method specified.
    int pivot_index = choose_pivot(arr, nel, width, comparator);

    // Swap the first element with the pivot element.
    SWAP(arr, arr + pivot_index * width, aux, width);

    // Partition the array around the pivot.
    int wall_index = partition(arr, aux, nel, width, comparator);

    // Sort the left and right subarrays.
    qsort(arr, aux, wall_index, width, comparator, choose_pivot);
    qsort(arr + (wall_index + 1) * width, aux, nel - wall_index - 1, width,
        comparator, choose_pivot);
}

static int partition(void *array, void *aux, size_t nel, size_t width,
    int (*comparator)(const void *, const void *))
{
    char *arr = (char *)array;

    // Partition the array around the pivot (first element).
    int wall_index = 0;
    for (size_t i = wall_index + 1, last = nel - 1; i <= last; i++)
        if (comparator(arr + i * width, arr) < 0)
            SWAP(arr + ++wall_index * width, arr + i * width, aux, width);

    // Swap the element at the wall with the pivot.
    SWAP(arr, arr + wall_index * width, aux, width);

    return wall_index;
}
