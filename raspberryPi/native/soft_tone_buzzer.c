//soft_tone_buzzer.c
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <softTone.h>

//gpio pin
#define BUZZER_PIN 12

int doReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

int main(){

    wiringPiSetupGpio(); //BCM 기준 gpio 핀번호 (gpio)사용한다는 설정
    pinMode(BUZZER_PIN, OUTPUT);

    //set PWM
    softToneCreate(BUZZER_PIN);
    while(1){
        for (int i = 0; i < 8; i++){
            softToneWrite(BUZZER_PIN, doReMi[i]);
            delay(100); //단위가 밀리초임
        }
    }
    return 0;
}