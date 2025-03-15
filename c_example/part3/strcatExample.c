//strcatExample.c
#include <stdio.h>
#include <string.h>


//strlen은 null 값은 제외하고 세준다
int main(void){
    const char *str1 = "hello, world"; //불변이기에 변화가능한 배열로 복사해서 바꿔주기
    char str2[] = "stack char array";
    int str1len = strlen(str1);
    int str2len = strlen(str2);
    printf("str1Len : %d str2Len : %d \n", str1len, str2len);

    char str3[30];
    strcpy(str3, str1);
    str3[0] = 'H';
    printf("%s\n", str3);

    if(strcmp(str1, str3) == 0){
        printf("두 문자열 str1, str2는 같다.\n");
    }else{
        printf("두 문자열은 %d 개만큼 다르다.\n", strcmp(str1, str3));
    }
    
    strcat(str3, str2);
    printf("%s\n", str3);

    return 0;
}