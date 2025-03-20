#include <avr/io.h>

void uart0Init(void)
{
    UCSR0A |= 0x00; // 2배속 모드
    UCSR0B = 0x18;       // 0b00011000 Rx, Tx enable
    UCSR0C = 0x06;      // 0b00010110  비동기, no Parity, 1 stop bit

    UBRR0H = 0x00;
    // UBRR0L = 207; // 115200 bps --> 9600 bsp  
    UBRR0L = 0x07;
}

void uart0Transmit(char data)
{
    while (!(UCSR0A & _BV(UDRE0))){
        ;
        UDR0 = data;
    }
}
unsigned char uart0Receive(void)
{
    while (!(UCSR0A & _BV(RXC0))) // 문자 버퍼에 있으면 루프 탈출
        ;
    return UDR0;
}
void uart0PrintString(char *str){
    for(int i = 0; str[i]; ++i){ // char값이 있으면 true / 없으면 false이기에 조금 위험할 수 있음
        uart0Transmit(str[i]);
        if(i>500){              //위 위험 사안에 대하여 사고방지 500자 이상시 종료
            break;
        }
    }
}
void uart0Print1ByteNumber(unsigned char n){    //교제에 있어서하지만 범용적인 함수는 아님
    uint8_t numString[4] = "0";
    int i, index = 0;
    if(n>0&& n<1000){
        for(int i = 0; n != 0; i++){
            //n=1,2,3이 들어가면
            numString[i] = n % 10 + '0'; // '3'으로 숫자가 문자로 바뀜 / 3 2 1로 들어감
            n = n / 10;
        }
        numString[i] = '\0';
        index = i - 1;

    }
    for(int i = index; i >= 0; i--){ // 들어간거 역순 출력이기에 1 2 3으로 출력됨 / 위에 numString에 대한 배열이 4로 설정되었기 때문에 4개가 나오지 않음
        uart0Transmit(numString[i]);
    }
}