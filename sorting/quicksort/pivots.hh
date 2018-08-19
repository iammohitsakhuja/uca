#include <cstddef>

#ifndef PIVOTS_HH
#define PIVOTS_HH

int choose_first_element_as_pivot(const void *array, size_t nel, size_t width,
    int (*comparator)(const void *, const void *));
int choose_last_element_as_pivot(const void *array, size_t nel, size_t width,
    int (*comparator)(const void *, const void *));
int choose_median_as_pivot(const void *array, size_t nel, size_t width,
    int (*comparator)(const void *, const void *));
int choose_random_pivot(const void *array, size_t nel, size_t width,
    int (*comparator)(const void *, const void *));

#endif
