//posZeroNeg.c
//숫자를 입력 받아서 양수, 제로, 음수를 출력하는 프로그램
//if else 구문으로 만드세요.
//printf는 한번만 쓰세요.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    
    int num;
    if (argc<2){
        printf("인자를 하나 넣어서 실행하세요\n");
        return 0;
    }
    num = atoi(argv[1]);
    char* a;
    
    if(num>0){
        a = "양수";
    }else if(num=0){
        a = "제로";
    }else if(num<0){
        a = "음수";
    }
    printf("입력한 수 %d 는 %s 입니다\n", num, a);
    

    return 0;
}