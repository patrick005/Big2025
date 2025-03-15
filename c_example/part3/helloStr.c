//helloStr.c
//문자열을 쓰는 두 가지 방법
#include <stdio.h>
#include <string.h>

int main(void){
    char *str1 = "hellow"; //변화를 줄 수 없다

    char str2[] = "hellow"; // 변화 가능
    char str3[] = {'h', 'e', 'l', 'l', 'o', 'w', '\0'};
    char str4= 'h';
    printf("%s\n",str1);
    printf("%s\n",str2);
    printf("%s\n",str3);
    printf("%c\n",str4);
    printf("%p\n",&str1);
    printf("%p\n",&str2);
    printf("%p\n",&str3);
    printf("%p\n",&str4);


    //str1[0] = 'H'; 컴파일 에러
    str2[0] = 'H';
    printf("%s\n",str2);

    return 0;
}