//charAdress.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char *str1 = "apple"; //데이터 영역임
    char str2[] = "apple";//스택영역이라 7로시작
    char *str3;             //힙영역
    str3 = (char *)malloc(sizeof(char) * 6);
    strcpy(str3, str2);
    printf("apple: %s, adress: %p\n", "apple", "apple");
    printf("str1: %s, adress: %p\n", str1, str1);
    printf("str2: %s, adress: %p\n", str2, str2);
    printf("str3: %s, adress: %p\n", str3, str3);

    free(str3);
    return 0;
}