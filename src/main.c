// // uart를 이용해서 시리얼 통신으로 센서 값을 0.1초 간격으로 출력 기능 추가하세요.-
// // --> CDS ADC_data : xxxx

// #include "lcd.h"
// #include "uart0.h"
// #include <avr/interrupt.h>
// #include <avr/io.h>
// #include <stdio.h>
// #include <string.h>
// #include <util/delay.h>

// volatile uint16_t adcResult = 0;
// volatile uint8_t power;
// volatile uint16_t timerCnt = 0;

// int main()
// {
//     uart0Init();
//     lcdInit();
//     stdin = &INPUT;
//     stdout = &OUTPUT;

//     DDRC = 0x0F; // 1, 2, 3, 4 출력 설정.

//     ADMUX = 0x40;   // ADC0 single mode, 0번 채널, 3.3V 외부 기준 전압(AREF)
//     ADCSRA = 0xAF;  // 10101111 ADC 허가, free running mode, Intterrupt en, 128 분주비
//     ADCSRA |= 0x40; // ADC 개시

//     TCCR0 = _BV(CS02) | _BV(CS00); // 타이머 0 설정, 분주비 1024
//     TIMSK = _BV(TOIE0);            // 타이머 0 오버플로우 인터럽트 활성화

//     sei();          // 전역 인터럽트 허용
    
//     lcdGotoXY(0, 0);
//     lcdPrintData("Light Sensor", 12);
//     char buf[16];
//     uint8_t onTime, offTime;
//     while (1)
//     {
//         lcdGotoXY(0, 1);
//         sprintf(buf, "L: %u", adcResult);
//         lcdPrintData(buf, strlen(buf));

//         // LED 밝기 조절
//         onTime = adcResult / 51; // 0 ~ 20 범위로 변환
//         if (onTime > 20)
//             onTime = 20;
//         offTime = 20 - onTime;

//         PORTC = 0x0F;
//         // 켜지는 시간 딜레이
//         for (int i = 0; i < onTime; ++i)
//             _delay_ms(15);
//         PORTC = 0x00;
//         // 꺼지는 시간 딜레이
//         for (int i = 0; i < offTime; ++i)
//             _delay_ms(15);
//         // // 시간 연산
//         // onTime = (adcResult - 300) / 35;
//         // if (onTime < 0)
//         //     onTime = 0;
//         // if (onTime > 20)
//         //     onTime = 20;
//         // offTime = 20 - onTime;
//         // PORTC = 0x0F;
//         // // 켜지는 시간 딜레이
//         // for (int i = 0; i < onTime; ++i)
//         //     _delay_ms(15);
//         // PORTC = 0x00;
//         // // 꺼지는 시간 딜레이
//         // for (int i = 0; i < offTime; ++i)
//         //     _delay_ms(15);
//     }
//     return 0;
// }

// ISR(ADC_vect)
// {
//     cli();
//     adcResult = ADC; // 2^16 -> 0 ~ 1023
//     sei();
// }

// ISR(TIMER0_OVF_vect) {
//     cli();
//     timerCnt++;
//     if (timerCnt >= 10) { // 0.1초마다
//         char uartBuf[32];
//         sprintf(uartBuf, "CDS ADC_data : %u\r\n", adcResult);
//         uart0PrintString(uartBuf);
//         timerCnt = 0;
//     }
//     sei();
// }

// uart를 이용해서 시리얼 통신으로 센서 값을 0.1초 간격으로 출력 기능 추가하세요.-
// --> CDS ADC_data : xxxx

// #include "lcd.h"
// #include "uart0.h"
// #include <avr/interrupt.h>
// #include <avr/io.h>
// #include <stdio.h>
// #include <string.h>
// #include <util/delay.h>

// volatile uint16_t adcResult = 0;

// int main() {
//     uart0Init();
//     lcdInit();

//     stdin = &INPUT;
//     stdout = &OUTPUT;

//     DDRB |= _BV(PB4); // OC0 핀 PB4 출력 설정

//     TCCR0 = _BV(WGM00) | _BV(WGM01) | _BV(COM01) | _BV(CS01); // Fast PWM 모드, 8분주

//     ADMUX = 0x40; // ADC0 single mode, 0번 채널, 3.3V 외부 기준 전압(AREF)
//     ADCSRA = 0xAF; // ADC 허가, free running mode, Interrupt en, 128 분주비
//     ADCSRA |= _BV(ADSC); // ADC 개시
//     sei();

//     printf("Hi, I'm Atmega128");

//     lcdGotoXY(0, 0);
//     lcdPrintData("Light Sensor", 12);

//     char buf[16];
//     uint8_t brightness = 0;

//     while (1) {
//         lcdGotoXY(0, 1);
//         sprintf(buf, "L: %u", adcResult);
//         lcdPrintData(buf, strlen(buf));
//         printf("CDS ADC_data : %u\r\n", adcResult);

//         // ADC 값을 0~255 범위로 변환하여 PWM 듀티 사이클 제어
//         brightness = adcResult / 2;
//         OCR0 = brightness;

//         // 필요에 따라 PORTC 제어 (예: PORTC의 특정 핀만 High로 설정)
//         PORTC |= _BV(PC0); // PC0 핀 High 설정
//         PORTC &= ~_BV(PC1); // PC1 핀 Low 설정

//         // 필요에 따라 LED 깜빡임 제어
//         // PORTC = 0x0F;
//         // _delay_ms(100);
//         // PORTC = 0x00;
//         // _delay_ms(100);
//     }

//     return 0;
// }

// ISR(ADC_vect) {
//     adcResult = ADC;
// }



// #include "lcd.h"
// #include <avr/delay.h>
// #include <avr/io.h>
// #include <stdlib.h>

// int main(void)
// {
//     DDRE = _BV(PE3); // PE3 출력 설정

//     TCCR3A = _BV(COM3A1) | _BV(WGM31);
//     TCCR3B = _BV(WGM33) | _BV(WGM32) | _BV(CS31);
//     // 분주비 8, fast PWM mode, timer3
//     ICR3 = 40000; // 20ms 2MHz -> 2000000 -> 1초 ? -> 0.02초
//     OCR3A = 3000; // 40000 : 20 = ? :1.5  2000~4000 -> -90 ~ 90

//     lcdInit();
//     lcdClear();
//     char buffer[16];

//     while (1)
//     {
//         for (uint16_t pulse = 800; pulse <= 4600; pulse += 100)
//         {
//             OCR3A = pulse;
//             itoa(pulse, buffer, 10);
//             lcdGotoXY(0, 0);
//             lcdPrint(buffer);
//             _delay_ms(20);
//         }
//         for (uint16_t pulse = 4600; pulse >= 800; pulse -= 100)
//         {
//             OCR3A = pulse;
//             itoa(pulse, buffer, 10);
//             lcdGotoXY(0, 0);
//             lcdPrint(buffer);
//             _delay_ms(20);
//         }
//     }
//     return 0;
// }


// PWM 설정 fast pwm, timer3, COM3A1 설정
// FND 설정
// 버저를 이용한 프로그램
// 버튼 인터럽트로 활성화 PE4, 5, 6, 7
// 버튼에 맞는 소리를 2초 동안 출력합니다. 2초 후에는 무음이 되어야 합니다.
// // FND 에 버튼이 눌린 번호(0, 1, 2, 3) 를 출력합니다.
// #include <avr/io.h>
// #include <util/delay.h>
// #include <avr/interrupt.h>

// #define PIEZO_PORT PORTB
// #define PIEZO_DDR DDRB
// #define PIEZO_PIN _BV(PB7)

// // 음이름-주파수 매핑
// #define B_FREQ 494
// #define G_FREQ 392
// #define F_FREQ 349
// #define E_FREQ 330
// #define A_FREQ 440

// // 멜로디 정보
// uint16_t melody_freq[] = {
//     B_FREQ, G_FREQ, F_FREQ, G_FREQ, F_FREQ, E_FREQ,
//     B_FREQ, G_FREQ, A_FREQ, B_FREQ, A_FREQ
// };

// float melody_duration_beats[] = {
//     0.5, 2.5, 0.5, 0.5, 1.5, 1.0,
//     0.5, 1.0, 0.125, 0.125, 0.125
// };

// uint16_t melody_duration[sizeof(melody_duration_beats) / sizeof(melody_duration_beats[0])];
// int melody_length = sizeof(melody_freq) / sizeof(melody_freq[0]);

// // BPM (Beats Per Minute) 설정
// #define BPM 120

// // 지연 함수
// void delay_ms(uint16_t ms) {
//     while (ms--) {
//         _delay_ms(1);
//     }
// }

// int main(void) {
//     // PB7 설정
//     PIEZO_DDR |= PIEZO_PIN;

//     // Timer 설정
//     TCCR1A = _BV(COM1C1) | _BV(WGM11); // Compare match, Fast PWM
//     TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // 분주비 1
//     TCCR1C = 0x00;

//     // 박자를 밀리초로 변환
//     float beat_duration_ms = 60000.0 / BPM;
//     for (int i = 0; i < melody_length; i++) {
//         melody_duration[i] = (uint16_t)(melody_duration_beats[i] * beat_duration_ms);
//     }

//     uint16_t i = 0; // 멜로디 인덱스

//     while (1) {
//         ICR1 = 14745600 / melody_freq[i]; // 주파수 설정
//         OCR1C = ICR1 / 2; // 듀티 사이클 50%
//         delay_ms(melody_duration[i]); // 지속 시간 반영

//         i++;
//         if (i >= melody_length) { // 멜로디 배열 반복
//             i = 0;
//         }
//     }

//     return 0;
// }

//
#include "lcd.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int main()
{
    lcdInit();
    lcdClear();
    char lcdBuffer[17];

    unsigned char switch_flag = 0;
    DDRE = 0x00;  // 8개의 핀을 모두 인풋!
    PORTE = 0x00; // 출력! - 풀업을 설정한다.
    DDRC = 0x0F;  // 아웃풋!
    // PINE
    while (1)
    {
        if (PINE >> 4)
        {
            switch_flag = PINE >> 4; // 0b1000 0b0100
        }
        PORTC = switch_flag;
        snprintf(lcdBuffer, sizeof(lcdBuffer), "SW: 0x%02X, %2d", switch_flag, /*'0' + */switch_flag);
        lcdGotoXY(0, 0);
        lcdPrint(lcdBuffer);
    }
    return 0;
}
