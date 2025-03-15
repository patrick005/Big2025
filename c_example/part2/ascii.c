//ascii.c
//0~127 아스키 코드를 출력하세요.
// 이중 for문으로 만드세요.
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
// 8줄 출력

#include <stdio.h>

int main(){
    char ch;
    for(int j = 0; j < 8 ; ++j ){//줄 8개


        //단수 0단~ 16단
        for(int i = 0; i<16; ++i){        
            ch = i + 16 * j;
            printf(" %d : %c    ", ch, ch);
            //printf(" %d", num);
        }

    }

    printf("\n");
    return 0;

}