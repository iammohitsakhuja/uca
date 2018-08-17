#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

void test_encoding(void);
void test_decoding(void);

int main(void)
{
    test_encoding();
    test_decoding();
    printf("All tests passed!\n");
    return 0;
}

static const char leviathan_quote[]
    = "Man is distinguished, not only by his reason, but by this singular "
      "passion from other animals, which is a lust of the mind, that by a "
      "perseverance of delight in the continued and indefatigable "
      "generation of knowledge, exceeds the short vehemence of any carnal "
      "pleasure.";
static char leviathan_encoded_quote[]
    = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCB"
      "ieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaC"
      "BpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZ"
      "GVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRp"
      "b24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW5"
      "5IGNhcm5hbCBwbGVhc3VyZS4=";

void test_encoding(void)
{
    char *encoding_result = NULL;

    encoding_result = encode("abcd");
    assert(strcmp(encoding_result, "YWJjZA==") == 0);
    free(encoding_result);

    encoding_result = encode("abcde");
    assert(strcmp(encoding_result, "YWJjZGU=") == 0);
    free(encoding_result);

    encoding_result = encode("abcdef");
    assert(strcmp(encoding_result, "YWJjZGVm") == 0);
    free(encoding_result);

    encoding_result = encode(leviathan_quote);
    assert(strcmp(encoding_result, leviathan_encoded_quote) == 0);
    free(encoding_result);

    printf("Encoding tests passed!\n");
}

void test_decoding(void)
{
    char *decoding_result = NULL;

    decoding_result = decode("YWJjZA==");
    assert(strcmp(decoding_result, "abcd") == 0);
    free(decoding_result);

    decoding_result = decode("YWJjZGU=");
    assert(strcmp(decoding_result, "abcde") == 0);
    free(decoding_result);

    decoding_result = decode("YWJjZGVm");
    assert(strcmp(decoding_result, "abcdef") == 0);
    free(decoding_result);

    decoding_result = decode(leviathan_encoded_quote);
    assert(strcmp(decoding_result, leviathan_quote) == 0);
    free(decoding_result);

    printf("Decoding tests passed!\n");
}
