#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PIEZO_PORT PORTB
#define PIEZO_DDR DDRB
#define PIEZO_PIN _BV(PB7)

// '학교 종이 땡땡땡' 멜로디 음계 (Hz)
uint16_t melody_freq[] = {
    392, 392, 440, 440, 392, 392, 330,
    392, 392, 330, 330, 294,
    392, 392, 440, 440, 392, 392, 330,
    392, 330, 294, 330, 262
};

// '학교 종이 땡땡땡' 멜로디 지속 시간 (ms)
uint16_t melody_duration[] = {
    250, 250, 250, 250, 250, 250, 500,
    250, 250, 250, 250, 750,
    250, 250, 250, 250, 250, 250, 500,
    250, 250, 250, 250, 750
};

int melody_length = sizeof(melody_freq) / sizeof(melody_freq[0]); // 멜로디 길이

// 지연 함수
void delay_ms(uint16_t ms) {
    while (ms--) {
        _delay_ms(1);
    }
}

int main(void) {
    // PB7 설정
    PIEZO_DDR |= PIEZO_PIN;

    // Timer 설정
    TCCR1A = _BV(COM1C1) | _BV(WGM11); // Compare match, Fast PWM
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // 분주비 1
    TCCR1C = 0x00;

    uint16_t i = 0; // 멜로디 인덱스

    while (1) {
        ICR1 = 14745600 / melody_freq[i]; // 주파수 설정
        OCR1C = ICR1 / 2; // 듀티 사이클 50%
        delay_ms(melody_duration[i]); // 지속 시간 반영

        i++;
        if (i >= melody_length) { // 멜로디 배열 반복
            i = 0;
        }
    }

    return 0;
}