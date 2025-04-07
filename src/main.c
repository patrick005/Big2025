// //i2c 쓰는 코드는 아니고 i2c가 들어간 헤더를 썻음
// #include "SHT2x.h" // i2c
// #include "TWI_driver.h"
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include "lcd.h"

// void printf_2dot1(uint8_t sense, uint16_t sense_temp);

// uint16_t temperaturC, humidityRH;

// int main(void)
// {   
//     Init_TWI();
//     lcdInit();  //lcd
//     SHT2x_Init(); //온습도
//     nt16 sRH;
//     nt16 sT;
//     uint8_t error; // SHT2x_MeasureHM가 선언된 헤더에서의 에러를 쓰기위해 그대로 가져옴

//     while (1)
//     {
//         error |= SHT2x_MeasureHM(HUMIDITY, &sRH);
//         error |= SHT2x_MeasureHM(TEMP, &sT);
//         temperaturC = SHT2x_CalcTemperatureC(sT.u16)*10; //해당 수식이 이미 sht2x.c 파일에 들어가있음
//         humidityRH = SHT2x_CalcRH(sRH.u16)* 10;          //이를 불러와 숫자로써 취급하여 출력
//         if(error == SUCCESS){
//             lcdGotoXY(0,0);
//             printf_2dot1(TEMP, temperaturC);        //잘뜨면 이 양식으로 출력해라
//             lcdGotoXY(0,1);
//             printf_2dot1(HUMIDITY, humidityRH);
//         }else{
//             lcdGotoXY(0,0);
//             lcdPrintData(" Temp: --.-C", 12);       //성공이 아니라면 --로 출력해라
//             lcdGotoXY(0,1);
//             lcdPrintData(" Humi: --.-%", 12);
//         }
//         _delay_ms(300);
//     }    
//     return 0;
// }

// void printf_2dot1(uint8_t sense, uint16_t sense_temp){

//     uint8_t s100, s10;
//     if(sense == TEMP){
//         lcdPrintData(" Temp: ", 7);
//         s100 = sense_temp / 100; // 100의 자리
//         if(s100> 0){
//             lcdDataWrite(s100 + '0');
//         }
//         s10 = sense_temp / 10 - s100 * 10; // 10의 자리
//         if(s10> 0){
//             lcdDataWrite(s10 + '0');
//         }
//         lcdDataWrite('.');
//         lcdDataWrite(sense_temp % 10 + '0'); // 1의 자리
//         lcdDataWrite('C');
//     }else if(sense == HUMIDITY){
//         lcdPrintData(" Humi: ", 7);
//         s100 = sense_temp / 100; // 100의 자리
//         if(s100> 0){
//             lcdDataWrite(s100 + '0');
//         }
//         s10 = sense_temp / 10 - s100 * 10; // 10의 자리
//         if(s10> 0){
//             lcdDataWrite(s10 + '0');
//         }
//         lcdDataWrite('.');
//         lcdDataWrite(sense_temp % 10 + '0'); // 1의 자리
//         lcdDataWrite('%');
//     }
// }

#include <avr/interrupt.h>
#include <avr/io.h>
#include <uart0.h>
#include "uart0.h"
#include <stdio.h>

// FILE OUTPUT = FDEV_SETUP_STREAM(uart0Transmit, NULL, _FDEV_SETUP_WRITE);    //stdio사용설정
// FILE INPUT = FDEV_SETUP_STREAM(NULL, uart0Receive, _FDEV_SETUP_READ);       //stdio사용설정

int main(){

    uart0Init();
    stdout = &OUTPUT;   //stdio사용설정
    stdin = &INPUT;     //stdio사용설정
    unsigned char rxData;
    uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
    DDRA = 0xff;

    printf("Hi, I'm Atmega128");
    fflush(stdout);
    while (1){
        printf("Hi, I'm Atmega128");
        fflush(stdout);
        // rxData = uart0Receive();
        scanf("%c", &rxData);

        if ((rxData >= 0x30) && (rxData <= 0x39)){
            PORTA = numbers[rxData - 0x30];
        }
    }
    return 0;
}
