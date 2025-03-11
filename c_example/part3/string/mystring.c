#include "mystring.h"

int my_strlen(const char *s){
    int i = - 1;
    do{
        ++i;
    }while(s[i] != '\0');
    return i;
}

void my_strcpy(char *des, const char *src){
    int i = 0;
    while(src[i] != '\0'){
        des[i] = src[i];
        ++i;
    }
    des[i] = '\0';
}

int my_strcmp(const char *s1, const char *s2){
    int result = 0;
    for(int i = 0; i < 1000; ++i){
        if(s1[i] == '0'){
            break;
        }
        if(s1[i]>s2[i]){
            result += 1;
        }
    }
    return result;
}

void my_strcat(char *des, const char *src){
    //des의 끝 인덱스 얻기
    int start = 0;
    while(des[start] != '\0'){
        ++start;
    }
    //des의 끝에서 하나씩 src char 를 붙이기
    int i = 0;
    while(src[i] != '\0'){
        des[start+i] = src[i];
        ++i;
    }
    //변경된 des의 마지막에 널문자 추가해주기
    des[start+i] = '\0';
}