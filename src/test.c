// //SHT 5초마다 한번씩 온습도 측정 - timer0 8비트 0.01초 기준 500번이면 될거고

// //외부 EEPROM의 주소는 0100 -> 온도, 0200 -> 습도 를 저장

// //SHT 에서 측정 실패는 error, 성공시에만 EEPROM에 저장

// //int4번 써서(스위치를 누르면) EEPROM에 데이터를 읽어서 UART로 출력 - 인터럽트4번에서 EEPROM데이터 읽기 및 출력

// //인터럽트: 개발보드에 고정되어있음



// #include "SHT2x.h" // i2c

// #include "TWI_driver.h"

// #include <avr/io.h>

// #include <avr/interrupt.h>

// #include <util/delay.h>

// #include "lcd.h"

// #include "uart0.h"

// #include "at25160.h"





// ISR(TIMER0_OVF_vect);

// uint8_t timer0Cnt = 0; //timer0 setting



// void printf_2dot1(uint8_t sense, uint16_t sense_temp);

// uint16_t temperaturC, humidityRH; 



// #define ARRAY_SIZE(array)(sizeof(array)/ sizeof(array[0])) // 송수신 데이터 사이즈 구하는 매크로

// //보내볼 데이터에 대한 예시 1,2,3



// int main(void){

//         //timer setting

//         TCCR0 = 0x07;

//         TCNT0 = 112;

//         TIMSK = 0x01;

//         TIFR = _BV(TOV0);

//         //온습도 setting

//         Init_TWI();

//         lcdInit();    //lcd

//         SHT2x_Init(); //온습도

//         nt16 sRH;

//         nt16 sT;

//         uint8_t error; // SHT2x_MeasureHM가 선언된 헤더에서의 에러를 쓰기위해 그대로 가져옴

//       

//         //메시지를 주고받을 버퍼 생성

//         uint8_t i = 0;

//         uint8_t buf1[20] = {0};

//         uint8_t buf2[20] = {0};

//       

//         SPI_Init(); //SPI 사용준비 / PB0 1 2 3이 이 교육보드에 할당 되어있음

//         lcdInit(); // lcd 사용준비 / PC4 5 6 7 PG2이 이 교육보드에 할당 되어있음

//         //송신 주소, 자료, 크기 설정

//         uint8_t msg1[] = temperaturC;

//         uint8_t msg2[] = humidityRH;

//         at25160_Write_Arry(0x0100, msg1, ARRAY_SIZE(msg1));

//         at25160_Write_Arry(0x0200, msg2, ARRAY_SIZE(msg2));

//         //수신

//         at25160_Read_Arry(0x0100, buf1, ARRAY_SIZE(buf1));

//         at25160_Read_Arry(0x0200, buf2, ARRAY_SIZE(buf2));

//         //buf 사이즈가 20으로 설정되어있기에 msg가 아무리 적어도 20개씩 들여옴

//       

//         sei();

//         while (1)

//         {

//                 error |= SHT2x_MeasureHM(HUMIDITY, &sRH);

//                 error |= SHT2x_MeasureHM(TEMP, &sT);

//                 temperaturC = SHT2x_CalcTemperatureC(sT.u16)*10; //해당 수식이 이미 sht2x.c 파일에 들어가있음

//                 humidityRH = SHT2x_CalcRH(sRH.u16)* 10;                    //이를 불러와 숫자로써 취급하여 출력



//                 if(timer0Cnt == 500){

//                         if(error == SUCCESS){

//                                 lcdGotoXY(0,0);

//                                 printf_2dot1(TEMP, temperaturC);                //잘뜨면 이 양식으로 출력해라

//                                 lcdGotoXY(0,1);

//                                 printf_2dot1(HUMIDITY, humidityRH);

//                               

//                         }else{

//                                 lcdGotoXY(0,0);

//                                 lcdPrintData(" Temp: --.-C", 12);             //성공이 아니라면 --로 출력해라

//                                 lcdGotoXY(0,1);

//                                 lcdPrintData(" Humi: --.-%", 12);

//                         }

//                         _delay_ms(300);      

//                 timer0Cnt = 0;

//                 }

//               

//         }      

//         return 0;

// }



// void printf_2dot1(uint8_t sense, uint16_t sense_temp){

//         uint8_t s100, s10;

//         if(sense == TEMP){

//                 lcdPrintData(" Temp: ", 7);

//                 s100 = sense_temp / 100; // 100의 자리

//                 if(s100> 0){

//                         lcdDataWrite(s100 + '0');

//                 }

//                 s10 = sense_temp / 10 - s100 * 10; // 10의 자리

//                 if(s10> 0){

//                         lcdDataWrite(s10 + '0');

//                 }

//                 lcdDataWrite('.');

//                 lcdDataWrite(sense_temp % 10 + '0'); // 1의 자리

//                 lcdDataWrite('C');

//         }else if(sense == HUMIDITY){

//                 lcdPrintData(" Humi: ", 7);

//                 s100 = sense_temp / 100; // 100의 자리

//                 if(s100> 0){

//                         lcdDataWrite(s100 + '0');

//                 }

//                 s10 = sense_temp / 10 - s100 * 10; // 10의 자리

//                 if(s10> 0){

//                         lcdDataWrite(s10 + '0');

//                 }

//                 lcdDataWrite('.');

//                 lcdDataWrite(sense_temp % 10 + '0'); // 1의 자리

//                 lcdDataWrite('%');

//         }

// }



// ISR(TIMER0_OVF_vect){

//         cli();

//         TCNT0 = 112; // 113 114 ~ 255 오버플로우 144-> 0.0025초

//         timer0Cnt++;

//         sei();

// }



// ISR(INT4_vect){

//         cli(); //전역설정을 없애는 역활

//       

//         sei();

// }