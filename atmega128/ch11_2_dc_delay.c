//ch11_2_dc_delay.c
#include <avr/delay.h>
#include <avr/io.h>

int main(void)
{   
    //모터 출력 설정
    DDRD= _BV(PD4)|_BV(PD5); // DC motor 4,5번핀 설정
    DDRB = _BV(PB5);

    //timer1 설정
    TCCR1A = _BV(COM1A1)| _BV(WGM11);   //interupt compare 설정
    TCCR1B = _BV(CS11) | _BV(WGM12)| _BV(WGM13); //  fastpwm 설정
    
    // fast PWM 분주비 8 -> 16MHz/8 = 2MHz
    ICR1 = 800; //2MHz : 1초 == 800Hz : x초 -> x = 1/2500초 == 0.0004초
    OCR1A = 560;  // 800 카운트 진행중 560번까지 5V 70%(560/800)
    
    while (1)
    {
        PORTD |= _BV(PD4); // M1 4번핀 정회전 입력
        PORTB |= _BV(PB5); // M1 회전 enable
        _delay_ms(1000);
        PORTD &= ~_BV(PD4); //정방향과 역방향 동시에 주면 안되기에 and비트연산을 통한 unset을 해줘야함
        //0bxxx1xxxx & 0b11101111 =>   0bxxx0xxxx
        PORTD |= _BV(PD5); // M1 5번핀 전압인가 / 역회전 입력 -> 속도 영향 받을지 강사님도 몰?루
        PORTB |= _BV(PB5); // M1 회전 enable
        _delay_ms(1000);
        
    }
    return 0;
}