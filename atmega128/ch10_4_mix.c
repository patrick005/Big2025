//ch10_4_mix.c
//SHT 5초마다 한번씩 온습도 측정 - timer0 8비트 0.01초 기준 500번이면 될거고
//외부 EEPROM의 주소는 0100 -> 온도, 0200 -> 습도 를 저장
//SHT 에서 측정 실패는 error, 성공시에만 EEPROM에 저장
//int4번 써서(스위치를 누르면) EEPROM에 데이터를 읽어서 UART로 출력 - 인터럽트4번에서 EEPROM데이터 읽기 및 출력
//인터럽트: 개발보드에 고정되어있음

#include "SHT2x.h" // I2C 통신을 위한 SHT2x 센서 라이브러리
#include "TWI_driver.h"
#include "at25160.h" // 외부 EEPROM(AT25160) 제어 라이브러리
#include <avr/io.h> // AVR 마이크로컨트롤러 입출력 레지스터 정의
#include <avr/interrupt.h> // AVR 인터럽트 관련 함수 및 매크로 정의
#include "uart0.h" // UART0 통신 라이브러리
#include <util/delay.h>

volatile uint8_t readFlag = 1, txFlag = 0;
uint16_t timer0Cnt = 0; // 타이머0 카운트 변수
uint16_t temperaturC, humidityRH; // 온도 및 습도 값을 저장할 변수

int main(void) {

    SPI_Init(); // SPI 통신 초기화

    // 온습도 센서 및 LCD, EEPROM 초기화
    Init_TWI(); // I2C 통신 초기화
    SHT2x_Init(); // SHT2x 센서 초기화
    uart0Init();
    
    DDRE = _BV(PE1);

    // interrupt 4 설정
    EICRB = 0x03; //int4 상승 엣지
    EIMSK = 0x10; //int4 허용

    TCCR0 = 0x07; // 분주비 1024 설정
    TCNT0 = 112; // 초기 카운트 값 설정 (0.01초 주기)
    TIMSK = 0x01; // 타이머0 오버플로우 인터럽트 활성화
    // TIFR = _BV(TOV0); // 타이머0 오버플로우 플래그 초기화
    sei(); // 전역 인터럽트 활성화
    stdout = &OUTPUT; //printf를 사용하기위한 선언

    while (1) {

        if(readFlag){
            // i2c temp read -> spi eeprom
            // 온습도 측정
            SHT2x_MeasureHM(TEMP, (nt16*)&temperaturC); // 온도 측정
            SHT2x_MeasureHM(HUMIDITY, (nt16*)&humidityRH); // 습도 측정
            // 측정된 온도/습도 값 계산
            temperaturC = SHT2x_CalcTemperatureC(temperaturC)*10; 
            humidityRH = SHT2x_CalcRH(humidityRH)*10;
            // EEPROM에 온도/습도 저장
            at25160_Write_Arry(0x0100, (uint8_t *)&temperaturC, 2); // 16비트를 8비트에 넣기위한 꼼수
            at25160_Write_Arry(0x0200, (uint8_t *)&humidityRH, 2);//이래 줄일 순 있지만 리틀엔디안 빅엔디안에서 꼬일수 있으니 테스트해봐서 써라
            readFlag = 0;
        }
        if(txFlag){
            // eeprom read -> uart printf
            // EEPROM에서 온도/습도 데이터 읽기
            at25160_Read_Arry(0x0100, (uint8_t *)&temperaturC, 2);
            at25160_Read_Arry(0x0200, (uint8_t *)&humidityRH, 2);
            // 읽어온 데이터 UART로 출력
            uart0PrintString("\n\rTemp: ");
            printf("%u.%u[C]", temperaturC/10, temperaturC%10);
            uart0PrintString("\n\rHumi: ");
            printf("%u.%u[%%]", humidityRH/10, humidityRH%10);
            
            txFlag = 0;
        }
    }
    return 0;
}

// 타이머0 오버플로우 인터럽트 서비스 루틴
ISR(TIMER0_OVF_vect) {
    timer0Cnt++; // 타이머0 카운트 증가
    if(timer0Cnt>= 500){ // 5초 확인
        timer0Cnt = 0;
        readFlag = 1;
    }
    TCNT0 = 112; // 타이머0 카운트 값 재설정
}

// INT4 인터럽트 서비스 루틴 (EEPROM 데이터 읽어 UART로 출력)
ISR(INT4_vect) {
    txFlag = 1;
}



