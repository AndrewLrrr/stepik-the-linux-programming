#include <stdio.h>

int main()
{
    int result1, result2;
    int count = 0;

    printf("Count is %d\n", count);

    result1 = stringStat("Andrew", 2, &count);
    printf("Multi 'Andrew' by %d. Result is: %d. Count is %d\n", 2, result1, count);

    result2 = stringStat("Alex", 5, &count);
    printf("Multi 'Alex' by %d. Result is: %d. Count is %d\n", 5, result2, count);

    return 0;
}