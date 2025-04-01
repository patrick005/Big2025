#include <stdio.h>
#include <wiringPi.h>

// led gpio pin (물리핀이 아닌 gpio핀 설정임)
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

int main(){

    wiringPiSetupGpio(); //BCM 기준 gpio 핀번호 (gpio)사용한다는 설정
    pinMode(LED1, OUTPUT);
    //pinMode(LED2, OUTPUT);
    //pinMode(LED3, OUTPUT);
    //pinMode(LED4, OUTPUT);

    while(1){
        digitalWrite(LED1, HIGH);
        //digitalWrite(LED2, HIGH);
        //digitalWrite(LED3, HIGH);
        //digitalWrite(LED4, HIGH);
    }
    printf("hello! RaspberryPi\n");


    return 0;
}