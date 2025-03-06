//posZeroNeg.c
//숫자를 입력 받아서 양수, 제로, 음수를 출력하는 프로그램
//if else 구문으로 만드세요.
//printf는 한번만 쓰세요.
#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    int num;
    printf("숫자를 넣으시오: ");
    scanf("%d", &num);

    //방법1
    // char *string;
    // if(num>0){
    //     string = "양수";
    // }else if(num<0){
    //     string = "음수";
    // }else{
    //     string = "제로";
    // }
    // printf("입력한 수 %d 는 %s 입니다\n", num, string);
    
    //방법2
    printf("입력한 수 %d 는 %s 입니다\n", num, num>0 ? "양수" : num<0 ? "음수" : "영");
    

    return 0;
}