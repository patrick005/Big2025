//2bit 증감 확인
#include <avr/io.h>
#include <util/delay.h>


int main(void){

    while (1){
        unsigned char led_data = 0x00;
        DDRC = 0x0F;
        while(1){
            PORTC = led_data;
            led_data++;
            if (led_data > 0x0F){
                led_data = 0;
            }
            _delay_ms(500);   
        }
    }
    

    return 0;
}