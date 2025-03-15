//sizeof.c
#include <stdio.h>
//#include <bits/types.h>
//#include <cstdint>
#include <stdint.h>

int main()
{
    int num;

    printf("sizeof(char): %ld\n", sizeof(char));
    printf("sizeof(short): %ld\n", sizeof(short));
    printf("sizeof(int): %ld\n", sizeof(int));
    printf("sizeof(long): %ld\n", sizeof(long));
    printf("sizeof(long long): %ld\n", sizeof(long long));
    printf("sizeof(float): %ld\n", sizeof(float));
    printf("sizeof(double): %ld\n", sizeof(double));
    printf("sizeof(num): %ld\n", sizeof(num));
    printf("sizeof(3.141592): %ld\n", sizeof(3.141592));
    printf("sizeof(uint32_t): %ld\n", sizeof(uint32_t));
    printf("sizeof(long double): %ld\n", sizeof(long double));
    
    return 0;
}