
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#define PIEZO_PORT PORTB
#define PIEZO_DDR  DDRB
#define PIEZO_PIN  _BV(PB7)

uint16_t doReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
// uint16_t doReMi[8] = {262, 294, 330, 349, 392, 440, 494, 523};
uint16_t piano = 0;
// '떴다떴다 비행기' 음계
uint8_t melody[24] = {4, 4, 5, 5, 4, 4, 2, 
                    4, 4, 2, 2, 1,
                    4, 4, 5, 5, 4, 4, 2,
                    4, 2, 1, 2, 0};


int main(void){

    //PF7 핀 피에조 --> 0cr1c
    DDRB = _BV(PB7); // 7번핀 출력설정

    TCCR1A = _BV(COM1C1)|_BV(WGM11);    //com 10 -> clear on compare
    TCCR1B = _BV(WGM13)|_BV(WGM12)|_BV(CS00); //분주비 1, fastPWM
    TCCR1C = 0x00;
    
    sei();      //전역 인터럽트 설정
    
    while (1){
        ICR1 = 14745600 / melody[piano]; // 주파수 만큼 duty cycle을 설정하겟다.
        OCR1C = ICR1 / 2; //절반을 on 시키겟다.
        piano++;
        if(piano>24){
            piano = 0;
        }
        _delay_ms(300);

    }
    return 0;
}
