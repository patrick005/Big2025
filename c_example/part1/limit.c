#include <stdio.h>
#include <limits.h>

int main()
{
    printf("hello, world\n");
    printf("char_bit : %d\n", CHAR_BIT);
    printf("char_bit : %d\n", CHAR_MAX);

    printf("INT_MAX : %d \t INT_MIN : %d\n", INT_MAX, INT_MIN);
    printf("LONG_MAX : %ld \t LONG_MIN : %ld\n", LONG_MAX, LONG_MIN);
    printf("INT_MAX + 1 : %d\n", INT_MAX );


    return 0;
}

