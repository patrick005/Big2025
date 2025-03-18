//led shift left to right
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
    DDRC = 0x0F;
    unsigned char led_data = 0x01; //기본 셋 1번만 들어오기
    unsigned char shift = 0;

    while (1) {
        
        if(led_data >= 0x08){ // 4번째꺼만 들어오면 2진수로 1000
            shift = 0; 
        }else if (led_data <= 0x01){ // 1번째꺼만 들어오면 2진수로 0001
            shift = 1; 
        }
            //쉬프트 연산으로 1000에서 0001로 1이 왔다리갔다리 구현
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