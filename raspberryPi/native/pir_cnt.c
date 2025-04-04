//pir_cnt.c
#include <stdio.h>
#include <wiringPi.h>

// gpio pin 
#define LED1_PIN 23
#define PIR_PIN 7

//void SW_ISR1(void);

int main(){

    wiringPiSetupGpio(); //BCM 기준 gpio 핀번호
    // wiringPiISR(PIR_PIN, INT_EDGE_RISING, /*&*/SW_ISR1);// 저거 붙이나 안붙이나 똑같지만 포인터로 넣어야해서 넣는게 맞는표현

    pinMode(LED1_PIN, OUTPUT);
    pinMode(PIR_PIN, INPUT);

    while(1){
        if(digitalRead(PIR_PIN) == HIGH){
            digitalWrite(LED1_PIN, HIGH);
            delay(300);
        }else{
            digitalWrite(LED1_PIN, LOW);
        }
    }
        return 0;
}

// void SW_ISR1(void){
//     delay(300);

//}