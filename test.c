#include <stdio.h>
int a = 100;
int *p;
p = &a;
*p = 200;

printf("%d", a);