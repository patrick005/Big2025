// 스위치를 활용한 led 제어
#include <stdio.h>
#include <wiringPi.h>

// gpio pin (물리핀이 아닌 gpio핀 설정임)
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1
#define SW1 4
#define SW2 17
#define SW3 27
#define SW4 22

int main(){

    wiringPiSetupGpio(); //BCM 기준 gpio 핀번호
    
    int led[4] = { LED1, LED2, LED3, LED4};
    int sw[4] = { SW1, SW2, SW3, SW4};

    for(int i = 0; i<4; ++i){
        pinMode(led[i], OUTPUT);
        pinMode(sw[i], INPUT);
        //digitalWrite(led[i], LOW);

    }

    while(1){
        for(int i = 0; i<4; ++i){
            if(digitalRead(sw[i])){
                digitalWrite(led[i], HIGH);
            }else{
                digitalWrite(led[i], LOW);
            }        
        }
    }
        return 0;
}