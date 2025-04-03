//hard_tone_buzzer.c
#include <stdio.h>
#include <wiringPi.h>

//gpio pin
#define BUZZER_PIN 26

int doReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

void setPWMFrequency(int freq); // 우리가 쓸거

int main(){

    wiringPiSetup(); //wiring pin
    pinMode(BUZZER_PIN, PWM_OUTPUT);

    while(1){
        for (int i = 0; i < 8; i++){
            setPWMFrequency(doReMi[i]); // 쓸거니 밑에 만들어야 할 거
            pwmWrite(BUZZER_PIN, 1000);
            delay(500);
        }
    }
    return 0;
}

void setPWMFrequency(int freq){
    int range = 2000;
    int clock = 19200000 / (range * freq); // 라즈베리파이 기본 클럭이 19.2MHz된다
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(range); //쿨럭을 나누는 틱의 갯수
    pwmSetClock(clock); // 
}