#include <cstdio>

#ifndef MERGE_SORT_HH
#define MERGE_SORT_HH

void merge_sort(void *array, size_t nel, size_t width,
    int (*comparator)(const void *a, const void *b));

#endif
