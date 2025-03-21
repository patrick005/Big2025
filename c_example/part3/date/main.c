#include "date.h"

int main(void){
    // Date d;
    // d.year = 2025;
    // d.month = 3;
    // d.day = 11;

    // Date d = {2024, 3, 11};

    Date d = {
        .year = 2025,
        .month = 3,
        .day = 11,
        .temp = {1, 2, 3, 4, 5, 6}};

    Date today;
    today = d;
    today.temp[0] = d.temp[0];//shallow copy
    printDate(&today);
    today.temp[0] = 10; // 배열이 복사 됨.
    printDate(&d);

    return 0;
}