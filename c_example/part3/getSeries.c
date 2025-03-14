//getSeries.c

#include <stdio.h>

int main(void){
 
    char ch;
    char str[100];

    printf("문자를 입력하세요: ");
    ch = getc(stdin);
    printf("입력한 문자는 %c 입니다.\n", ch);

    ch = getchar();
    printf("입력한 문자는 %c 입니다.\n", ch);

    scanf("%s", str);
    printf("입력한 문자열는 %s 입니다.\n", str);
    // printf("입력한 문자는 %s%*c 입니다.\n", str);
    //%*c를 추가하면 개행문자를 무시할 수 있다.

    //버퍼에 개행문자가 있다.
    //getchar();

    return 0;
}