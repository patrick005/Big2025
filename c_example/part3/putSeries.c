//putSeries.c
#include <stdio.h>
 
int main(void){

    FILE *fp;
    fp = fopen("output.txt", "a");
    if (fp == NULL){
        printf("파일 열기 실패");
        return 1;
    }
    putc('A', fp);      //파일에 넣기
    putc('A', stdout);  //화면에 출력
    fputc('B', fp);     //파일에 넣기
    fputc('B', stdout); //화면에 출력
    // gets deprecicate 지원 종료 -> 더이상 사용 할 수 없음
    fputs("puts로 문자가 간다.", fp);
    fputs("puts로 문자가 간다.", stdout);
    
    fprintf(fp, "printf로 문자가 간다");
    // fflush(fp);
    fprintf(stdout, "printf로 문자가 간다");
    // fflush(stdout);
    // EOF == -1;
    fclose(fp);
    return 0;
}