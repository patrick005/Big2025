//filePointer.c
//파일을 생성하는 첫번째 방법
//리소스에 여유가 있을 때 사용하는 방법
#include <stdio.h>

int main(void){
    FILE *a;
    a = fopen("test.dat", "w");
    if ( a == NULL){
        printf("cna't open file\n");
        return 1;
    }
    fprintf(a, "이것은 파일로 저장되는 예시 데이터 입니다.");
    fclose(a);

    return 0;
}