//pointer2.c

#include <stdio.h>


int main(void){
    int var_a;
    int *pVar_a;
    int **ppVar_a;
    //참조
    var_a = 100;
    pVar_a = &var_a;
    ppVar_a = &pVar_a;
    //역참조
    **ppVar_a = 200;
    printf("var_a: %d, &var_a: %p\n", var_a, &var_a);
    printf("pVAr_a: %p, *pVar_a: %d\n", pVar_a, *pVar_a);
    printf("ppVAr_a: %p, *ppVar_a: %p, **ppVar_a: %d\n", ppVar_a, *ppVar_a, **ppVar_a);

    return 0;
}