#include <cstdio>
#include <cstdlib>

#include "pivots.hh"

#pragma GCC diagnostic ignored "-Wunused-parameter"

int choose_first_element_as_pivot(
    const void *, size_t, size_t, int (*)(const void *, const void *))
{
    return 0;
}

int choose_last_element_as_pivot(
    const void *, size_t nel, size_t, int (*)(const void *, const void *))
{
    return nel - 1;
}

int choose_median_as_pivot(const void *array, size_t nel, size_t width,
    int (*comparator)(const void *, const void *))
{
    int first  = 0;
    int last   = nel - 1;
    int middle = (first + last) / 2;

    char *arr = (char *)array;

    // If middle < first.
    if (comparator(arr + middle * width, arr + first * width) < 0) {
        // If middle >= last.
        if (comparator(arr + middle * width, arr + last * width) >= 0)
            return middle;
        // Else if middle < last && last < first.
        else if (comparator(arr + last * width, arr + first * width) < 0)
            return last;
    } else if (comparator(arr + middle * width, arr + first * width) > 0) {
        // Else if middle > first.
        // If middle <= last
        if (comparator(arr + middle * width, arr + last * width) <= 0)
            return middle;
        // Else if middle > last && last > first
        else if (comparator(arr + last * width, arr + first * width) > 0)
            return last;
    }

    return first;
}

int choose_random_pivot(
    const void *, size_t nel, size_t, int (*)(const void *, const void *))
{
    return rand() % nel;
}
