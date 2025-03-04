#include <stdio.h>

int main()
{
    double fahr;
    fahr = 200;
    printf("fahr temp : %f\n", fahr);

    int celsius;
    celsius = (fahr - 32) * 5 / 9;
    printf("fahrenheit temp : %f --> celsius temp : %d\n", fahr, celsius);

    
    return 0;
}