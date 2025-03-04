#include <stdio.h>

int main()
{
    int celsius;
    //celsius = 15;
    printf("Input celsius temp : ?\n");
    scanf("%d", &celsius);
    printf("celsius temp : %d \n", celsius);

    double fahr;
    // 9/5 ->1 b.s int
    fahr = 9.0 / 5.0 * celsius + 32;
    printf("fahr temp : %f\n", fahr);

    return 0;
}