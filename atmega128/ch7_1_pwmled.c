
#include <avr/io.h>
#include <avr/interrupt.h>


int main(void){

    DDRC = 0x00;
    DDRB |= _BV(PB4);
    TCCR0 = _BV(WGM00)|_BV(WGM01)|_BV(COM01)|_BV(CS01); //clock select 8 prescale
    // fast PWM. compare -> clear(counting)
    // 16000000 Hz / 8 -> 2MHz / 255 -> 7845Hz dutycycle
    // 1 / 7845 ->0.00012s = 0.12ms [0.02 on / 0.08 off nomarl]
    uint8_t brightness = 0;
    int8_t delta = 1;

    while (1){
        OCR0 = brightness; //0~255 -> 이 숫자로 compare가 일어남
        _delay_ms(10);
        brightness += delta;
        if(brightness ==0 || brightness == 255){
            delta = -delta;
        }
    }
    return 0;
}


