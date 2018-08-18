#include "merge_sort.hh"
#include <cstdlib>
#include <cstring>

void merge_sort(void *array, size_t nel, size_t width,
    int (*comparator)(const void *a, const void *b));
static void msort(void *array, void *aux, int first, int last, size_t width,
    int (*comparator)(const void *a, const void *b));
static void merge(void *array, void *aux, int first, int middle, int last,
    size_t width, int (*comparator)(const void *a, const void *b));

void merge_sort(void *array, size_t nel, size_t width,
    int (*comparator)(const void *a, const void *b))
{
    // Create an auxiliary array once, in order to save repetitive malloc
    // calls.
    void *aux = (void *)malloc(nel * sizeof(void *) * width);

    // Sort the array.
    msort(array, aux, 0, nel - 1, width, comparator);

    // Housekeeping.
    free(aux);
}

static void msort(void *array, void *aux, int first, int last, size_t width,
    int (*comparator)(const void *a, const void *b))
{
    if (first == last)
        return;

    int middle = (first + last) / 2;

    // Sort the left subarray.
    msort(array, aux, first, middle, width, comparator);

    // Sort the right subarray.
    msort(array, aux, middle + 1, last, width, comparator);

    // Merge the two subarrays.
    merge(array, aux, first, middle, last, width, comparator);
}

static void merge(void *array, void *aux, int first, int middle, int last,
    size_t width, int (*comparator)(const void *a, const void *b))
{
    char *arr  = (char *)array;
    char *temp = (char *)aux;

    // Copy elements into the auxiliary array.
    for (int i = first; i <= last; i++)
        memcpy(temp + i * width, arr + i * width, width);

    // Merge the 2 subarrays.
    int i = first;
    int j = middle + 1;
    int k = first;
    while (i <= middle && j <= last) {
        if (comparator(temp + i * width, temp + j * width) <= 0)
            memcpy(arr + k++ * width, temp + i++ * width, width);
        else
            memcpy(arr + k++ * width, temp + j++ * width, width);
    }

    // Copy over any remaining elements, if any.
    while (i <= middle)
        memcpy(arr + k++ * width, temp + i++ * width, width);

    while (j <= last)
        memcpy(arr + k++ * width, temp + j++ * width, width);
}
