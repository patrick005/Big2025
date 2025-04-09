#include <stdio.h>

void my_strcpy(char *des, const char *src){
    /*int i;
    for(i = 0; src[i]!=0; ++i){
        des[i] = src[i]; 
     
    }
    des[i] = '\0';*/
    while (*des++ = *src++){
        ;
    }
}

int main(void){
    char str[100];
    char *str2 = "hello, world";

    my_strcpy(str, str2);
    printf("str1: %s\n", str);

    return 0;
}