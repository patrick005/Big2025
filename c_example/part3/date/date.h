#pragma once

typedef struct{
    int year;
    int month;
    int day;
    int temp[6];
}Date;


void printDate(Date *);