#include <avr/interrupt.h>
#include <avr/io.h>
#include "uart0.h"

int main(){   
    uart0Init();
    unsigned char rxData;
    uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
    DDRA = 0xff;

    while (1){
        rxData = uart0Receive();
        if ((rxData >= 0x30) && (rxData <= 0x39)){
            PORTA = numbers[rxData - 0x30];
        }
    }
    return 0;
}