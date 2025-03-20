// timer 2번을 써서 led 좌우로 움직이는 코드 작성 0.3초마다 움직이기
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t ledData = 0x01;
uint8_t timer2Cnt = 0;
uint8_t shift = 0;

ISR(TIMER0_OVF_vect);

int main(void){
    DDRC = 0x0F;

    TCCR2 = _BV(CS22)| _BV(CS20); // 1024 prescale Hz
    // TCNT0 = 112;
    TIMSK = _BV(TOIE2);       //timer interrupt en.
    // TIFR = _BV(TOV0);
    
    sei();
    while (1){
        PORTC = ledData;
        if(timer2Cnt == 30){
            if(shift == 0){
                ledData <<= 1;
                if(ledData == 0x08){
                    shift = 1;
                }
            }else{
                ledData >>=1;
                if(ledData == 0x01){
                    shift = 0;
                }
            }
        timer2Cnt = 0;
        }
    }
    return 0;
}

ISR(TIMER2_OVF_vect){
    cli();
    TCNT2 = 112; // 113 114 ~ 255 오버플로우 144-> 0.0025초
    timer2Cnt++;
    sei();
}
