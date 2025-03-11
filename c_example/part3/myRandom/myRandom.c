// myRandom.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void my_srand(int s);
int my_rand(void);

int main(void)
{
    my_srand(time(NULL));
    for (int i = 0; i < 10; ++i)
    {
        int num = my_rand();
        printf("%d ,", num);
    }
    printf("\n");
    return 0;
}

int seed = 1;
void my_srand(int s)
{
    seed = s;
}

int my_rand(void)
{
    seed = seed * 11035152245 + 12345;
    return ((unsigned)(seed / 65535)) % 32768;
}