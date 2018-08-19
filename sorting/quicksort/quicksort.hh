#include <cstddef>

#ifndef QUICKSORT_HH
#define QUICKSORT_HH

void quicksort(void *array, size_t nel, size_t width,
    int (*comparator)(const void *, const void *),
    int (*choose_pivot)(
        const void *, size_t, size_t, int (*)(const void *, const void *)));

#endif
