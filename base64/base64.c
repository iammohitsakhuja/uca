#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

static void base64_encoding(
    const char *input, unsigned int input_length, char *result);
static void base64_decoding(
    const char *input, unsigned int input_length, char *result);

static const char *lookup_table
    = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// clang-format off
static const char ascii_table[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
    -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};
// clang-format on

char *encode(const char *string)
{
    // Calculate the size of the resulting string.
    int input_length = strlen(string);
    int length       = (input_length + 2) / 3 * 4;
    char *result     = (char *)calloc(length + 1, sizeof(char));

    base64_encoding(string, input_length, result);

    return result;
}

char *decode(const char *string)
{
    // Calculate the size of the resulting string.
    int input_length = 0;
    while (string[input_length] != '=' && string[input_length] != '\0'
        && ++input_length)
        ;
    int length   = (input_length + 2) / 4 * 3;
    char *result = (char *)calloc(length + 1, sizeof(char));

    base64_decoding(string, input_length, result);

    return result;
}

static void base64_encoding(
    const char *input, unsigned int input_length, char *result)
{
    unsigned int result_index = 0;
    unsigned int i;
    for (i = 0; i < input_length - 2; i += 3) {
        result[result_index++] = lookup_table[(input[i] >> 2) & 0x3F];
        result[result_index++] = lookup_table[((input[i] << 4) & 0x30)
            | ((input[i + 1] >> 4) & 0x0F)];
        result[result_index++] = lookup_table[((input[i + 1] << 2) & 0x3C)
            | ((input[i + 2] >> 6) & 0x03)];
        result[result_index++] = lookup_table[input[i + 2] & 0x3F];
    }

    // Will only execute if the input length wasn't a multiple of 3.
    if (i < input_length) {
        result[result_index++] = lookup_table[(input[i] >> 2) & 0x3F];

        if (i == input_length - 1) {
            result[result_index++] = lookup_table[(input[i] << 4) & 0x30];
            result[result_index++] = '=';
        } else { /* If input length % 3 == 1 */
            result[result_index++] = lookup_table[((input[i] << 4) & 0x30)
                | ((input[i + 1] >> 4) & 0x0F)];
            result[result_index++] = lookup_table[(input[i + 1] << 2) & 0x3C];
        } /* Else if input length % 3 == 2 */
        result[result_index++] = '=';
    }

    result[result_index++] = '\0';
}

static void base64_decoding(
    const char *input, unsigned int input_length, char *result)
{
    unsigned int result_index = 0;
    unsigned int i;
    for (i = 0; i < input_length - 3; i += 4) {
        result[result_index++] = ((ascii_table[(int)input[i]] << 2) & 0xFC)
            | ((ascii_table[(int)input[i + 1]] >> 4) & 0x03);
        result[result_index++] = ((ascii_table[(int)input[i + 1]] << 4) & 0xF0)
            | ((ascii_table[(int)input[i + 2]] >> 2) & 0x0F);
        result[result_index++] = ((ascii_table[(int)input[i + 2]] << 6) & 0xC0)
            | (ascii_table[(int)input[i + 3]] & 0x3F);
    }

    // Will only execute if the input contained '='s.
    if (i < input_length) {
        result[result_index++] = ((ascii_table[(int)input[i]] << 2) & 0xFC)
            | ((ascii_table[(int)input[i + 1]] >> 4) & 0x03);

        // If the input string has 2 '='s.
        if (i == input_length - 3) {
            result[result_index++]
                = ((ascii_table[(int)input[i + 1]] << 4) & 0xF0)
                | ((ascii_table[(int)input[i + 2]] >> 2) & 0x0F);
        }
        result[result_index++] = '\0';
    }
}
