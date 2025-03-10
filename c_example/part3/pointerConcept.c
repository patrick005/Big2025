//pointerConcept.c

#include <stdio.h>
 
int main(void){
    int var_a;
    int var_b=0;
    int *pVar;

    var_a = 100;
    pVar = &var_b; // 포인터는 변수의 연결을 해야한다.
    *pVar = 200;    // 포인터는 반드시 대상을 가리키고 역참조를 해야한다.
    printf("var_a : %d, &var_a : %p\n", var_a, &var_a);
    printf("*pVar : %d, pVar : %p\n", *pVar, pVar);
    printf("var_b : %d, &var_b : %p\n", var_b, &var_b);

    return 0;
}