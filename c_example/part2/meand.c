//meand.c
#include <stdio.h>

int main(){

    int sosu = 10;
    int result = 0;

    for(int i = 2; i <= sosu; i++){
        int count = 0;

        for(int j = 2; j <= i; j++){

            if(i % j == 0){
                count ++;
            }else
                continue;

        }
        if(count == 1){
            result++;
        }
    }
    
printf("0부터 %d까지 소수의 개수는 %d개 입니다.\n", sosu, result);

    return 0;
}