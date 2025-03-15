//leafYear.c
#include <stdio.h>   //pirntf, scanf에 대해 사용할 수 있게 하는 헤더파일
#include <stdbool.h> //true, false에 대해 사용할 수 있게 하는 헤더파일

int main()
{
    int year;
    while (true){
        printf("년도를 넣으세요: ");
        scanf("%d", &year);
        // if(year % 4 == 0){
        //     printf("%d 년도는 윤년입니다.\n", year);
        // } else{
        //     printf("%d 년도는 평년입니다.\n", year);
        // }
        // if(!year)
        //     break;
        
        printf("%d 년도는 %s입니다.\n", year, year%4 ? "평년" : "윤년");
        if(!year) break;
    }
    
    

    return 0;
}