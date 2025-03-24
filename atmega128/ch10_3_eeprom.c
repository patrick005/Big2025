//ch10_3_eeprom.c
#include "lcd.h"
#include <avr/delay.h>
#include <avr/io.h>
#include "at25160.h"

#define ARRAY_SIZE(array)(sizeof(array)/ sizeof(array[0])) // 송수신 데이터 사이즈 구하는 매크로
//보내볼 데이터에 대한 예시 1,2,3
uint8_t msg1[] = "welcome!!";
uint8_t msg2[] = "ATmega128-world";
uint8_t msg3[] = "SPI-Flash Example";

int main(void)
{   
    //메시지를 주고받을 버퍼 생성
    uint8_t i = 0;
    uint8_t buf1[20] = {0};
    uint8_t buf2[20] = {0};
    uint8_t buf3[20] = {0};

    SPI_Init(); //SPI 사용준비 / PB0 1 2 3이 이 교육보드에 할당 되어있음
    lcdInit(); // lcd 사용준비 / PC4 5 6 7 PG2이 이 교육보드에 할당 되어있음
    
    //송신 주소, 자료, 크기 설정
    at25160_Write_Arry(0x0100, msg1, ARRAY_SIZE(msg1));
    at25160_Write_Arry(0x0200, msg2, ARRAY_SIZE(msg2));
    at25160_Write_Arry(0x0300, msg3, ARRAY_SIZE(msg3));

    //수신
    at25160_Read_Arry(0x0100, buf1, ARRAY_SIZE(buf1));
    at25160_Read_Arry(0x0200, buf2, ARRAY_SIZE(buf2));
    at25160_Read_Arry(0x0300, buf3, ARRAY_SIZE(buf3));
    //buf 사이즈가 20으로 설정되어있기에 msg가 아무리 적어도 20개씩 들여옴

    //3가지 방법으로 출력
    while (1)
    {
        lcdGotoXY(0, 0);
        for(i =0; i< ARRAY_SIZE(msg1) -1; i++){
            lcdDataWrite(buf1[i]);
            _delay_ms(100);
        }
        i=0;
        lcdGotoXY(0,1);
        while(buf2[i]){
            lcdDataWrite(buf2[i]);
            ++i;
            _delay_ms(100);
        }

        lcdGotoXY(0, 0);
        lcdPrint(buf3);
        _delay_ms(2000);
        lcdClear();
    }    
    return 0;
}