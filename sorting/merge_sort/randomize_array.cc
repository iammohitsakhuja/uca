#include <cstdlib>
#include <cstring>

#include "randomize_array.hh"

#define SWAP(a, b, width)                                                     \
    do {                                                                      \
        char *__a  = a;                                                       \
        char *__b  = b;                                                       \
        char *temp = (char *)malloc(width);                                   \
        memcpy(temp, __a, width);                                             \
        memcpy(__a, __b, width);                                              \
        memcpy(__b, temp, width);                                             \
        free(temp);                                                           \
    } while (0);

/**
 * NOTE: rand() must be seeded in the program that uses this function.
 */
void randomize_array(void *array, size_t nel, size_t width)
{
    char *arr = (char *)array;

    do {
        int i = rand() % nel--;
        SWAP(arr + i * width, arr + nel * width, width);
    } while (nel);
}
