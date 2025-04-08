#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void){

    int size;
    scanf("%d", &size);

    //malloc() / free()
    int *p = malloc(sizeof(int)*size);
    //double *p = malloc(sizeof(double)*size);

    assert(p /*!= NULL*/);
    // NULL이 왜 0 취급이지?

    for (int i = 0; i < size; i++){
        p[i] = i;
    }
    for (int i = 0; i < size; i++){
        printf("%d\n", p[i]);
    }

    free(p);
    return 0;
}