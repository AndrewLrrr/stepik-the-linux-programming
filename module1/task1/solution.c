#include <string.h>

int stringStat(const char *string, size_t multiplier, int *count)
{
    size_t str_len;

    *count = *count + 1;
    str_len = strlen(string);

    return str_len * multiplier;
}