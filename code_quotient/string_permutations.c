#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void swap(char *a, char *b)
{
  	char temp = *a;
  	*a = *b;
  	*b = temp;
}

char **all_permutations = NULL;
int j = 0;

void permutations(char *str, int begin, int end)
{
  	// If the recursive call has reached the last character,
  	// it means that all other characters are fixed.
  	// Hence, string can be added to all permutations in its current state.
  	if (begin == end) {
      	strcpy(all_permutations[j], str);
      	j++;
    } else {
      	for (int i = begin; i <= end; i++) {
          	// Swap and fix a character.
          	swap(&str[begin], &str[i]);
          	permutations(str, begin + 1, end);

          	// Swap the character back.
          	swap(&str[begin], &str[i]);
        }
    }
}

int char_comparator(const void *a, const void *b)
{
  	return *(char *)a - *(char *)b;
}

int string_comparator(const void *a, const void *b)
{
  	return strcmp(*(const char **) a, *(const char **) b);
}

int factorial(int n)
{
  	if (n <= 0)
      	return 1;

  	return n * factorial(n - 1);
}

void printPermute(char *str)
{
  	int length = strlen(str);
  	qsort(str, length, sizeof(char), char_comparator);

  	int fact_length = factorial(length);
  	all_permutations = (char **)malloc(fact_length * sizeof(char *));
  	for (int i = 0; i < fact_length; i++) {
      	all_permutations[i] = (char *)calloc(length + 1, sizeof(char));
    }

	permutations(str, 0, length - 1);
  	j = 0;

  	qsort(all_permutations, fact_length, sizeof(char *), string_comparator);

  	for (int i = 0; i < fact_length; i++)
      	printf("%s ", all_permutations[i]);

  	for (int i = 0; i < fact_length; i++)
      	free(all_permutations[i]);
  	free(all_permutations);
}

