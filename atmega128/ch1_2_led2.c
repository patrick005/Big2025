#include <avr/io.h>
#include <util/delay.h>


int main(void){

    while (1){
        DDRC = 0x03; //0b0011 0,1번 출력 모드로 한다.
        //*(volatile uint8_t *)(0x14) = 0x03;
        
        PORTC = 0x0F; //0b1111 0,1,2,3번을 1(on)로 만든다 -> 5V 출력
        //상위비트만 계승하고 하위비트는 변경
        //PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3);
        // 01 10 100 1000 or 연산 때려서임
        //PORTC |= _BV(PC0) | _BV(PC1) | _BV(PC2) | _BV(PC3);
        _delay_ms(500);
        
        PORTC = 0x00; // 0000 0,1,2,3번을 0(off)로 만든다 -> 0V 출력
        _delay_ms(500);
    }
    

    return 0;
}