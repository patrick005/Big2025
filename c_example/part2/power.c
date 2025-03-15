//power.c
// n의 제곱을 구하는 함수를 만들어서 2의 62 제곱을 프린트하시오

#include <stdio.h>


long long power(int base, int exponent);
void power2(int base, int exponent, long long *result2);


int main(void){
    
    long long result = power(2, 62); //int 32bit -> 2^32
    printf("2 power of 62 = %lld\n", result);
    long long result2 = 1;
    power2(2, 62, &result2);
    printf("2 power of 62 = %lld\n", result2);

    return 0;
}



long long power(int base, int exponent){
    
    long long result = 1;
    for(int i = 0; i< exponent; i++)
        result *= base;

    return result;
}

void power2(int base, int exponent, long long *result2){
    for(int i = 0; i< exponent; i++)
        *result2 *= base;

}
