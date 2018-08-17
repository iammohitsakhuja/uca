#include <stdio.h>

/* Include other headers as needed */
int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int length;
    scanf("%i", &length);
    int array[length];
    for (int i = 0; i < length; i++)
        scanf("%i", &array[i]);
    // Calculate the cumulative XOR.
    int xor_all = array[0];
    for (int i = 1; i < length; i++)
        xor_all = xor_all ^ array[i];
    // Get the rightmost set bit of this cumulative XOR.
    int set_bit = xor_all & (~(xor_all - 1));
    // Calculate the cumulative XORs of the two parts of the array.
    int xor1 = 0;
    int xor2 = 0;
    for (int i = 0; i < length; i++)
    {
        if (set_bit & array[i])
            xor1 = xor1 ^ array[i];
        else
            xor2 = xor2 ^ array[i];
    }
    if (xor1 < xor2)
        printf("%i %i\n", xor1, xor2);
    else
        printf("%i %i\n", xor2, xor1);
    return 0;
}
