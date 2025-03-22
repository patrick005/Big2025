// PULSE값에 따른 -90 ~ 90도 설정 완료
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <stdlib.h>

int main(void){
    DDRE = _BV(PE3);
    TCCR3A = _BV(COM3A1)| _BV(WGM31);
    TCCR3B = _BV(WGM33)| _BV(WGM32)| _BV(CS31);
    //분주비 8, fast PWM mode, timer3
    ICR3 = 40000; // 20ms -> 16MHz/8 = 2MHz -> 200000 (1sec)*x = 0.02sec
    OCR3A = 3000; // 40000: 20 = ? : 1.5 2000~4000 -> -90 ~ 90

    lcdInit();
    lcdClear();

    char buffer[16];

    while(1){
        for(uint16_t pulse = 800; pulse <= 4600; pulse += 40){
            OCR3A = pulse;
            itoa(pulse, buffer, 10);
            lcdGotoXY(0,0);
            lcdPrint(buffer);
            
        }
        _delay_ms(20);
        for(uint16_t pulse = 4600; pulse >= 800; pulse -= 40){
            OCR3A = pulse;
            itoa(pulse, buffer, 10);
            lcdGotoXY(0,0);
            lcdPrint(buffer);
            
        }
        _delay_ms(20);
    }

}