// serial.c
// 현대 차의 자동차 번호를 출력하는 프로그램
// int count = 0;
// extern int count;
#include "serial.h"
int getSerialNumber(void)
{
    static int count = 0;
    int result = count;
    ++count;
    return result;
    // return count++;
}