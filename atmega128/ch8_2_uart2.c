#include <avr/interrupt.h>
#include <avr/io.h>
#include <uart0.h>
#include "uart0.h"
#include <stdio.h>

FILE OUTPUT = FDEV_SETUP_STREAM(uart0Transmit, NULL, _FDEV_SETUP_WRITE);    //stdio사용설정
FILE INPUT = FDEV_SETUP_STREAM(NULL, uart0Receive, _FDEV_SETUP_READ);       //stdio사용설정

int main(){

    uart0Init();
    stdout = &OUTPUT;   //stdio사용설정
    stdin = &INPUT;     //stdio사용설정
    unsigned char rxData;
    uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
    DDRA = 0xff;

    printf("Hi, I'm Atmega128");
    fflush(stdout);
    while (1){
        printf("Hi, I'm Atmega128");
        fflush(stdout);
        // rxData = uart0Receive();
        scanf("%c", &rxData);

        if ((rxData >= 0x30) && (rxData <= 0x39)){
            PORTA = numbers[rxData - 0x30];
        }
    }
    return 0;
}