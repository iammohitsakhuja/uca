#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_word(int num);
void test(void);

int main(void)
{
    test();
    printf("All tests passed!\n");
    return 0;
}

void test(void)
{
    char *string = NULL;
    string = int_to_word(10);
    assert(strcmp(string, "ten") == 0);
    free(string);

    string = int_to_word(328674);
    assert(strcmp(string,
        "three lakhs twenty eight thousand six hundred seventy four") == 0);
    free(string);

    string = int_to_word(999999);
    assert(strcmp(string,
        "nine lakhs ninety nine thousand nine hundred ninety nine") == 0);
    free(string);

    string = int_to_word(12345);
    assert(strcmp(string, "twelve thousand three hundred forty five") == 0);
    free(string);

    string = int_to_word(0);
    assert(strcmp(string, "zero") == 0);
    free(string);

    string = int_to_word(7);
    assert(strcmp(string, "seven") == 0);
    free(string);

    string = int_to_word(14);
    assert(strcmp(string, "fourteen") == 0);
    free(string);

    string = int_to_word(21);
    assert(strcmp(string, "twenty one") == 0);
    free(string);

    string = int_to_word(100);
    assert(strcmp(string, "one hundred") == 0);
    free(string);

    string = int_to_word(888);
    assert(strcmp(string, "eight hundred eighty eight") == 0);
    free(string);

    string = int_to_word(1298);
    assert(strcmp(string, "one thousand two hundred ninety eight") == 0);
    free(string);

    string = int_to_word(28674);
    assert(strcmp(string,
        "twenty eight thousand six hundred seventy four") == 0);
    free(string);
}

// Handles upto 6 digits.
char *int_to_word(int num)
{
    // Hard coded arrays for reference.
    char single_digits[10][6] = {"zero", "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine"};
    char ten_to_twenty[10][10] = {"ten", "eleven", "twelve", "thirteen",
        "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char tens[10][8] = {"zero", "ten", "twenty", "thirty", "forty", "fifty",
        "sixty", "seventy", "eighty", "ninety"};

    int array[6] = {0};

    // Store the number in the array, in reverse order.
    for (int temp = num, i = 5; temp > 0; temp /= 10, i--)
        array[i] = temp % 10;

    // Create a string.
    char *word = (char *)calloc(100, sizeof(char));

    bool space_required = false;
    bool all_zeroes = true;
    // Deal with lakhs.
    if (array[0] != 0) {
        strcat(word, single_digits[array[0]]);
        if (array[0] == 1)
            strcat(word, " lakh");
        else
            strcat(word, " lakhs");

        space_required = true;
        all_zeroes = false;
    }

    // Deal with thousands.
    if (array[1] != 0 || array[2] != 0) {
        // Add a space after 'lakhs'.
        if (space_required)
            strcat(word, " ");

        if (array[1] == 1) {
            strcat(word, ten_to_twenty[array[2]]);
        } else if (array[1] != 0) {
            strcat(word, tens[array[1]]);
            strcat(word, " ");
            strcat(word, single_digits[array[2]]);
        } else {
            strcat(word, single_digits[array[2]]);
        }

        strcat(word, " thousand");

        space_required = true;
        all_zeroes = false;
    }

    // Deal with hundreds.
    if (array[3] != 0) {
        // Add a space after 'thousand'.
        if (space_required)
            strcat(word, " ");

        strcat(word, single_digits[array[3]]);
        strcat(word, " hundred");

        space_required = true;
        all_zeroes = false;
    }

    // Deal with tens.
    if (array[4] != 0) {
        // Add a space after 'hundred'.
        if (space_required)
            strcat(word, " ");

        if (array[4] == 1)
            strcat(word, ten_to_twenty[array[5]]);
        else {
            strcat(word, tens[array[4]]);

            if (array[5] != 0) {
                strcat(word, " ");
                strcat(word, single_digits[array[5]]);
            }
        }

        all_zeroes = false;
    } else if (all_zeroes || array[5] != 0) {
        // Add a space, if required.
        if (space_required)
            strcat(word, " ");

        strcat(word, single_digits[array[5]]);
    }

    return word;
}
