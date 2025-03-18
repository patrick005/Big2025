//led shift left to right
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
    DDRC = 0x0F;
    unsigned char led_data = 0x01;
    unsigned char shift = 0;

    while (1) {
        
        if(led_data == 0x08){
            shift = 0; 
        }else if (led_data == 0x01){
            shift = 1; 
        }

        if(shift == 0){
            led_data >>= 1;
        }else if(shift == 1){
            led_data <<= 1;
        }
        PORTC = led_data;
        _delay_ms(500);
    }

    return 0;
}