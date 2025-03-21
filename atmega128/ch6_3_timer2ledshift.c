// LED를 0.3 초 간격으로 좌우로 움직이세요. 
// timer3을 써서 인터럽트 구현
// 분주비는 256을 사용
// 인터럽트가 0.3초마다 일어나게 하세요
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
volatile uint8_t ledData = 0x01;
volatile uint8_t shift;

int main(void){
    DDRC = 0x0F;

    TCCR3A = 0x00;
    TCCR3B = _BV(CS32); // 분주비 1 16MHz 16000000/65536 = 244.144Hz
    //분주비 1024 16MHz 16000000/1024 = 15625 Hz --> 65535 - 15625 = 49910
    //16000000/256 = 62500Hz --> *0.3 -> 18750  --> 65536 - 18750 => 46786

    ETIMSK = _BV(TOIE3); 
    TCNT3 = 46786;
    sei();
    while (1){
        _delay_ms(100);
    }
    return 0;
}

ISR(TIMER3_OVF_vect){
    cli();
    TCNT3 = 46786;
    if (ledData >= 0x08){
        shift = 0;
    }
    if (ledData == 0x01){
        shift = 1;
    }
    if (shift){
        ledData <<= 1;
    }else{
        ledData >>= 1;
    }
    PORTC = ledData;
    sei();
}
