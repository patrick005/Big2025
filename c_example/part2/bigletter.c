//bigletter.c
//임의의 char를 scanf로 하나 받아서 대문자인지 소문자인지 출력하세요.
#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    char a ;
    printf("문자를 넣으시오: ");
    scanf("%c", &a);

    //방법1
    if('A'<= a && a <= 'Z'){
        printf(" %c는 대문자입니다.\n",a);
    }else if('a'<= a && a<= 'z'){
        printf(" %c는 소문자입니다.\n",a);
    }else{
        printf(" %c는 영문자가 아닙니다.\n",a);
    }

   
    //방법2
    //printf("입력한 문자 %c는 %s 입니다\n", a, (int)a >=97 ? "소문자" : "대문자");
    

    return 0;
}