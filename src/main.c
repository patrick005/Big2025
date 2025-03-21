
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t numbers[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
// {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7C, 0X07,0X7F, 0X67,0X77,0X7C, 0X39, 0X5E, 0X79,0X71, 0X08,0X80};
// {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};

volatile uint8_t timeS = 0x01;
// volatile uint8_t fndFlag =0, edgeFlag = 0;

int main(void){

    DDRA = 0xFF; //FND led 출력 설정
    DDRE = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x05; 
    //분주비 1024
    OCR1A = 14400;
    OCR1B = 28800;
    TIMSK = _BV(OCIE1A)| _BV(OCIE1B)| _BV(TOIE1);   //compare 인터럽트 enable
    // ETIMSK = ETIMSK = _BV(TOIE3) | _BV(TICIE3);
    // ETIFR = _BV(ICF3);
    sei();
    PORTA = numbers[0];
    while (1){
        PORTA = numbers[timeS];
    //     if(fndFlag){
    //         if(timeS > 10){
    //             timeS = 10;
    //         }
    //         PORTA = numbers[timeS];
    //         fndFlag = 0;
    //     }
        if(timeS>10){
            timeS = 0;
        }
    }
    return 0;
}

ISR(TIMER1_COMPA_vect){
    cli();
    // OCR1A += 14400;
    timeS++;
    
    sei();
}

ISR(TIMER1_COMPB_vect){
    cli();
    // OCR1B -= 14400;
    timeS--;
    
    sei();
}

ISR(TIMER1_OVF_vect){
    cli();
    timeS++;
    sei();
}

