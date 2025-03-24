//ch11_3_dc_delay.c
#include "lcd.h"
#include <avr/delay.h>
#include <avr/io.h>

int main(void)
{   
    uint8_t pwmDuty = 60, cntDir = 0;
    //모터 출력 설정
    DDRD= _BV(PD4)|_BV(PD5); // DC motor 4,5번핀 설정
    DDRB = _BV(PB5);

    //timer1 설정
    TCCR1A = _BV(COM1A1)| _BV(WGM11);   //interupt compare 설정
    TCCR1B = _BV(CS11) | _BV(WGM12)| _BV(WGM13); //  fastpwm 설정
    
    // fast PWM 분주비 8 -> 16MHz/8 = 2MHz
    ICR1 = 800; //2MHz : 1초 == 800Hz : x초 -> x = 1/2500초 == 0.0004초
    OCR1A = 8 * pwmDuty;  
    
    lcdInit();
    lcdGotoXY(0, 0);
    lcdPrintData(" Duty: ", 7);

    PORTD |= _BV(PD4); // M1 4번핀 정회전 입력
    PORTB |= _BV(PB5); // M1 회전 enable

    while (1)
    {
        if(cntDir){
            pwmDuty-= 5;
            if(pwmDuty <0){   //0~100이기에 넘어갔을때의 처리
                cntDir = 0;
            }
        }else{
            pwmDuty+= 5;
            if(pwmDuty > 99){   //0~100이기에 넘어갔을때의 처리
                cntDir = 1;
            }
        }
        OCR1A = 8 * pwmDuty; // 0~100
        lcdGotoXY(7, 0);
        lcdDataWrite((pwmDuty/10)%10 +'0'); // 10의 자리수
        lcdDataWrite(pwmDuty%10 +'0');      // 1의 자리수
        lcdDataWrite('%');
    
    }
    return 0;
}