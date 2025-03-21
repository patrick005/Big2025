// PWM 설정 fast pwm, timer3, COM3A
// FND 설정
// 버저를 이용한 프로그램 버저는 pb7
// 버튼 인터럽트로 활성화 PE4, 5, 6, 7
// 버튼에 맞는 소리를 2초간 출력합니다 
// FND에 버튼이 눌린 번호를 출력합니다.
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FND_PORT PORTA
#define FND_DDR DDRA

#define BUZZER_PORT PORTB
#define BUZZER_DDR DDRB
#define BUZZER_PIN PB7

#define BUTTON_PORT PINE
#define BUTTON_PIN_4 PE4
#define BUTTON_PIN_5 PE5
#define BUTTON_PIN_6 PE6
#define BUTTON_PIN_7 PE7

uint16_t frequencies[] = {262, 294, 330, 349}; // 도, 레, 미, 파
uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
volatile uint8_t button_pressed = 0;

void setup_timer1_pwm(uint16_t frequency) { // 타이머 3 대신 타이머 1 사용
    TCCR1A = _BV(COM1C1) | _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);
    ICR1 = 16000000 / frequency;
    OCR1C = ICR1 / 2;
}

void play_sound(uint8_t sound_index) {
    setup_timer1_pwm(frequencies[sound_index]);
    _delay_ms(2000);
    TCCR1A &= ~(_BV(COM1C1));
}

void display_fnd(uint8_t number) {
    FND_PORT = numbers[number];
}

ISR(INT4_vect) {
    button_pressed = 1;
    display_fnd(1);
    play_sound(0);
}

ISR(INT5_vect) {
    button_pressed = 2;
    display_fnd(2);
    play_sound(1);
}

ISR(INT6_vect) {
    button_pressed = 3;
    display_fnd(3);
    play_sound(2);
}

ISR(INT7_vect) {
    button_pressed = 4;
    display_fnd(4);
    play_sound(3);
}

int main(void) {
    FND_DDR = 0xFF;
    BUZZER_DDR |= _BV(BUZZER_PIN); // 버저 핀 출력 설정
    DDRE &= ~(_BV(BUTTON_PIN_4) | _BV(BUTTON_PIN_5) | _BV(BUTTON_PIN_6) | _BV(BUTTON_PIN_7));
    PORTE |= _BV(BUTTON_PIN_4) | _BV(BUTTON_PIN_5) | _BV(BUTTON_PIN_6) | _BV(BUTTON_PIN_7);

    EICRB = _BV(ISC41) | _BV(ISC51) | _BV(ISC61) | _BV(ISC71);
    EIMSK = _BV(INT4) | _BV(INT5) | _BV(INT6) | _BV(INT7);

    sei();

    while (1) {
        _delay_ms(5000);
    }

    return 0;
}