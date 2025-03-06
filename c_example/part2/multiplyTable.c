//multiplyTable.c

#include <stdio.h>

int main(){

    for(int i = 2; i<=9; ++i){
        //단수 2단~ 9단
        printf(" \n%d 단 입니다. \n",i);
        for(int j = 1; j <= 9 ; ++j ){ // 2부터 9까지
            printf("%d X %d = %d \t",i, j, i*j);

        }

    }
    printf("\n");

    return 0;

}