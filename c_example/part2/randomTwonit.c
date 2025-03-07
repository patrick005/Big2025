//randomTwonit.c
//두 난수를 발생 시켜서 비교하기
// 10 까지의 수를 비교해서 같은 값이 나오면 반복작업 종료
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


int main(void){

    int a, b, i;
    double rand1, rand2;
    while(true){
        i++;
        srand((unsigned int)time(NULL));
        //랜덤 셋 시간을 숫자로 변환함
        rand1 = rand()/(double)RAND_MAX*10;
        srand((unsigned int)time(NULL)+i+10000);
        ////동시간대 처리된다면 같은 값이 나올 수 있기에 한번 꼬아줘야 할 때 이렇게 함
        rand2 = rand()/(double)RAND_MAX*10;
        //0~1까지의 랜덤한 숫자를 만드는데 *100을 하여 -~100사이의 랜덤숫자를 생성케 함
        printf("0~100 사이의 랜덤한 숫자: %f\n", rand1);
        printf("0~100 사이의 랜덤한 숫자: %f\n", rand2);

        a = rand1;
        b = rand2;
        //a, b를 int로 지정해뒀기 때문에 rand를 엮으면 타입캐스팅을 추가로 안 해도 됌
        printf("%d > %d : %s\n", a, b, a > b ? "true" : "false");
        printf("%d < %d : %s\n", a, b, a < b ? "true" : "false");
        printf("%d == %d : %s\n", a, b, a == b ? "true" : "false");
        printf("%d != %d : %s\n", a, b, a != b ? "true" : "false");
        
        if (a == b)
        break;
    }

    return 0;
}