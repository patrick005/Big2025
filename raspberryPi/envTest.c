// #include <dotenv.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    // char * buf =  malloc(10);
    // buf = getenv("name");
    printf("name: %s", getenv("name"));
    // getenv("age");
    printf("age: %s", getenv("age"));
    // free(buf);
    return 0;
}