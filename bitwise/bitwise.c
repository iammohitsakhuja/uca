#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// Bitwise functions.
int bit_and(int x, int y);
int bit_xor(int x, int y);
int sign(int x);
int logical_shift(int x, int n);
int get_byte(int x, int n);
int bang(int x);
int conditional(int x, int y, int z);
int is_power_of_2(int x);

// Test prototypes.
void test_bitand(void);
void test_bitxor(void);
void test_sign(void);
void test_logical_shift(void);
void test_get_byte(void);
void test_bang(void);
void test_conditional(void);
void test_is_power_of_2(void);

int main(void)
{
    test_bitand();
    test_bitxor();
    test_sign();
    test_logical_shift();
    test_get_byte();
    test_bang();
    test_conditional();
    test_is_power_of_2();
    printf("All tests passed!\n");
    return 0;
}

void test_bitand(void)
{
    assert(bit_and(0, 0) == (0 & 0));
    assert(bit_and(1, 1) == (1 & 1));
    assert(bit_and(-1, -1) == (-1 & -1));
    assert(bit_and(0, 1) == (0 & 1));
    assert(bit_and(0, -1) == (0 & -1));
    assert(bit_and(1, -1) == (1 & -1));
    assert(bit_and(4, 1) == (4 & 1));
    assert(bit_and(5, 13) == (5 & 13));
    assert(bit_and(23, 38) == (23 & 38));
}

void test_bitxor(void)
{
    assert(bit_xor(0, 0) == (0 ^ 0));
    assert(bit_xor(1, 1) == (1 ^ 1));
    assert(bit_xor(-1, -1) == (-1 ^ -1));
    assert(bit_xor(0, 1) == (0 ^ 1));
    assert(bit_xor(0, -1) == (0 ^ -1));
    assert(bit_xor(1, -1) == (1 ^ -1));
    assert(bit_xor(4, 1) == (4 ^ 1));
    assert(bit_xor(5, 13) == (5 ^ 13));
    assert(bit_xor(23, 38) == (23 ^ 38));
}

void test_sign(void)
{
    assert(sign(1) == 1);
    assert(sign(0) == 0);
    assert(sign(-1) == -1);
    assert(sign(2343) == 1);
    assert(sign(-2344) == -1);
    assert(sign(10) == 1);
    assert(sign(-10) == -1);
}

void test_logical_shift(void)
{
    assert(logical_shift(-1, 1) == INT_MAX);
    assert(logical_shift(1, 1) == 0);
    assert(logical_shift(13, 2) == 3);
    assert(logical_shift(3, 2) == 0);
}

void test_get_byte(void)
{
    assert(get_byte(0x01020304, 0) == 4);
    assert(get_byte(0x01020304, 1) == 3);
    assert(get_byte(0x01020304, 2) == 2);
    assert(get_byte(0x01020304, 3) == 1);
    assert(get_byte(0x347f32dd, 0) == 221);
    assert(get_byte(0x347f32dd, 1) == 50);
    assert(get_byte(0x347f32dd, 2) == 127);
    assert(get_byte(0x347f32dd, 3) == 52);
}

void test_bang(void)
{
    assert(bang(0) == 1);
    assert(bang(1) == 0);
    assert(bang(-1) == 0);
    assert(bang(334) == 0);
    assert(bang(-334) == 0);
    assert(bang(10) == 0);
    assert(bang(-10) == 0);
}

void test_conditional(void)
{
    assert(conditional(1, 3, 5) == 3);
    assert(conditional(2, 3, 5) == 3);
    assert(conditional(-1, 342, 5) == 342);
    assert(conditional(0, 342, 5) == 5);
    assert(conditional(0, -243, 78) == 78);
}

void test_is_power_of_2(void)
{
    assert(is_power_of_2(0) == 0);
    assert(is_power_of_2(1) == 1);
    assert(is_power_of_2(2) == 1);
    assert(is_power_of_2(3) == 0);
    assert(is_power_of_2(4) == 1);
    assert(is_power_of_2(5) == 0);
    assert(is_power_of_2(6) == 0);
    assert(is_power_of_2(7) == 0);
    assert(is_power_of_2(8) == 1);
    assert(is_power_of_2(13) == 0);
    assert(is_power_of_2(16) == 1);
    assert(is_power_of_2(32) == 1);
    assert(is_power_of_2(94) == 0);
    assert(is_power_of_2(-34) == 0);
}

int bit_and(int x, int y)
{
    return ~(~x | ~y);
}

int bit_xor(int x, int y)
{
    int a = ~x & y;
    int b = x & ~y;
    return ~(~a & ~b);
}

int sign(int x)
{
    return x >> 31 | ((~x + 1) >> 31 & !!x);
}

int logical_shift(int x, int n)
{
    int mask = ~(((1 << 31) >> n) << 1);

    return mask & (x >> n);
}

int get_byte(int x, int n)
{
    return x >> (n << 3) & 0xff;
}

int bang(int x)
{
    return (x >> 31 | (~x + 1) >> 31) + 1;
}

int conditional(int x, int y, int z)
{
    int mask = x >> 31 | (~x + 1) >> 31;

    return (mask & y) | (~mask & z);
}

int is_power_of_2(int x)
{
    return !(x & (x + (~1 + 1))) + (~!x + 1);
}
