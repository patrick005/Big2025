//one2tensum.c
//

#include <stdio.h>

int main(){

    int sum = 0;
    
    // for(int i = 0; i < 9901; ++i){
    //     sum += i + 100;
    // }

    for(int i = 100; i <= 10000; ++i){
        sum += i;
    }


    printf("100부터 10000까지 더한 숫자는 %d 입니다.\n", sum);
    return 0;
}