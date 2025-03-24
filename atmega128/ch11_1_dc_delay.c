//ch11_1_dc_delay.c
//DC motor 정방향과 역방향 회전 예제
#include <avr/delay.h>
#include <avr/io.h>

int main(void)
{   
    //출력 설정
    DDRD= _BV(PD4)|_BV(PD5); // DC motor 4,5번핀 설정
    DDRB = _BV(PB5);
    
    while (1)
    {
        PORTD |= _BV(PD4); // M1 4번핀 정회전 입력
        PORTB |= _BV(PB5); // M1 회전 enable
        _delay_ms(1000);
        PORTD &= ~_BV(PD4); //정방향과 역방향 동시에 주면 안되기에 and비트연산을 통한 unset을 해줘야함
        //0bxxx1xxxx & 0b11101111 =>   0bxxx0xxxx
        PORTD |= _BV(PD5); // M1 5번핀 전압인가 / 역회전 입력
        PORTB |= _BV(PB5); // M1 회전 enable
        _delay_ms(1000);
        
    }
    return 0;
}