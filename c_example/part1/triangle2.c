#include <stdio.h>

int main(void){

    double length;
    double height;
    double area;

    printf("fnter triangle's length : ");
    scanf("%lf", &length);
    printf("fnter triangle's height : ");
    scanf("%lf", &height);
    area = length * height / 2.0;
    printf("triangle's area is : %.2f\n", area);

    return 0;
}