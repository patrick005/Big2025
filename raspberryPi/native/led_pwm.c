//led_pwm.c
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

// led gpio pin
#define LED1 23
#define LED2 24
#define LED3 25
#define LED4 1

int main(){

    wiringPiSetupGpio(); //BCM 기준 gpio 핀번호 (gpio)사용한다는 설정
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    //set PWM
    softPwmCreate(LED1, 255, 255); //풀 출력
    softPwmCreate(LED2, 100, 255); //중간 출력
    softPwmCreate(LED3, 0, 255);   //출력 없음 
    softPwmCreate(LED4, 0, 255);   //출력 없음 
    while(1){
        for (int i = 0; i < 255; i++){
            softPwmWrite(LED4, i);
            delay(100); //단위가 밀리초임
        }
    }
    return 0;
}