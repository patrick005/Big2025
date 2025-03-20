#include <avr/interrupt.h>
#include <avr/io.h>
#include <uart0.h>
#include "uart0.h"
#include "lcd.h"
#include <stdio.h>

volatile uint8_t intData = '0';
uint8_t cursor = 0;

int main(){

    uart0Init();
    lcdInit();
    stdout = &OUTPUT;   //stdio사용설정
    stdin = &INPUT;     //stdio사용설정
    
    DDRE = 0x02;        //Rx0(입력), Tx(출력)1, sw0~3 입력 - 없어도 작동하지만 명시하기위함
    
    EICRB = 0xff;       //4567 상승엣지에서 동작
    EIMSK = 0xf0;       //0123 허용
    EIFR = 0xf0;        //4567 클리어
    
    sei();      //전역 인터럽트 허용
    
    char cData;

    printf("Hi, I'm Atmega128");
    fflush(stdout);
    lcdGotoXY(0,0);
    while (1){
        
        if(intData != '0'){
            printf("\n\r Input Switch : %c", intData);
            intData = '0';
        }
        while(UCSR0A & (1<<RXC0)){
            // TODO:  4개 문자 이상 못받아 오는 문제 버퍼 문제 해결
            cData = fgetc(stdin);
            // UCSR0A |= _BV(RXC0);
        
            lcdDataWrite(cData);
            cursor++;
            if(cursor == 16){
                lcdGotoXY(0,1);
            }else if(cursor == 32){
                cursor = 0;
                lcdGotoXY(0,0);
            }
        }
    }
    return 0;
}

ISR(INT4_vect){
    cli(); //전역설정을 없애는 역활
    intData = '1';
    sei();
}
ISR(INT5_vect){
    cli(); //전역설정을 없애는 역활
    intData = '2';
    sei();
}
ISR(INT6_vect){
    cli(); //전역설정을 없애는 역활
    intData = '3';
    sei();
}
ISR(INT7_vect){
    cli(); //전역설정을 없애는 역활
    intData = '4';
    sei();
}
//interrupt 관련 내용이 무거우면 우선순위가 높기에 pwm을 돌릴때 안돌아갈 수도있음

