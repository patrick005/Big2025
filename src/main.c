#include "SHT2x.h" // I2C 통신을 위한 SHT2x 센서 라이브러리
#include "TWI_driver.h" // I2C 통신 드라이버
#include <avr/io.h> // AVR 마이크로컨트롤러 입출력 레지스터 정의
#include <avr/interrupt.h> // AVR 인터럽트 관련 함수 및 매크로 정의
#include <util/delay.h> // 지연 함수 제공
#include "lcd.h" // LCD 제어 라이브러리
#include "uart0.h" // UART0 통신 라이브러리
#include "at25160.h" // 외부 EEPROM(AT25160) 제어 라이브러리

ISR(TIMER0_OVF_vect); // 타이머0 오버플로우 인터럽트 서비스 루틴 선언
uint8_t timer0Cnt = 0; // 타이머0 카운트 변수
void printf_2dot1(uint8_t sense, uint16_t sense_temp); // 온도/습도 값을 LCD에 출력하는 함수 선언
uint16_t temperaturC, humidityRH; // 온도 및 습도 값을 저장할 변수

#define ARRAY_SIZE(array)(sizeof(array)/ sizeof(array[0])) // 배열 크기 계산 매크로

int main(void) {
    // 타이머0 설정
    TCCR0 = 0x07; // 분주비 1024 설정
    TCNT0 = 112; // 초기 카운트 값 설정 (0.01초 주기)
    TIMSK = 0x01; // 타이머0 오버플로우 인터럽트 활성화
    TIFR = _BV(TOV0); // 타이머0 오버플로우 플래그 초기화

    nt16 sRH; // 습도 값 저장 변수
    nt16 sT; // 온도 값 저장 변수
    uint8_t error = 0; // SHT2x 측정 오류 플래그
    
    // 온습도 센서 및 LCD, EEPROM 및 SPI 초기화
    Init_TWI(); // I2C 통신 초기화
    SHT2x_Init(); // SHT2x 센서 초기화
    SPI_Init(); // SPI 통신 초기화
    lcdInit(); // LCD 초기화 (중복 호출)

    // EEPROM에 저장할 온도/습도 데이터 버퍼
    uint8_t temp_buf[2];
    uint8_t humi_buf[2];

    // EEPROM에서 읽어온 데이터 저장 버퍼
    // uint8_t read_temp_buf[2];
    // uint8_t read_humi_buf[2];

    sei(); // 전역 인터럽트 활성화

    while (1) {
        // 온습도 측정
        error |= SHT2x_MeasureHM(HUMIDITY, &sRH); // 습도 측정
        error |= SHT2x_MeasureHM(TEMP, &sT); // 온도 측정

        // 측정된 온도/습도 값 계산
        temperaturC = SHT2x_CalcTemperatureC(&sT) * 10;
        humidityRH = SHT2x_CalcRH(&sRH) * 10;

        // 5초마다 LCD에 온도/습도 출력 및 EEPROM에 저장
        if (timer0Cnt == 500) {
            if (error == SUCCESS) {
                // LCD에 온도/습도 출력
                lcdGotoXY(0, 0);
                printf_2dot1(TEMP, temperaturC);
                lcdGotoXY(0, 1);
                printf_2dot1(HUMIDITY, humidityRH);

                // EEPROM에 온도/습도 저장
                temp_buf[0] = (temperaturC >> 8) & 0xFF;
                temp_buf[1] = temperaturC & 0xFF;
                humi_buf[0] = (humidityRH >> 8) & 0xFF;
                humi_buf[1] = humidityRH & 0xFF;

                at25160_Write_Arry(0x0100, temp_buf, 2);
                at25160_Write_Arry(0x0200, humi_buf, 2);
            } else {
                // 측정 실패 시 LCD에 오류 메시지 출력
                lcdGotoXY(0, 0);
                lcdPrintData(" Temp: --.-C", 12);
                lcdGotoXY(0, 1);
                lcdPrintData(" Humi: --.-%", 12);
            }
            _delay_ms(300);
            timer0Cnt = 0;
        }
    }
    return 0;
}

// 온도/습도 값을 LCD에 출력하는 함수
void printf_2dot1(uint8_t sense, uint16_t sense_temp) {
    uint8_t s100, s10;
    if (sense == TEMP) {
        lcdPrintData(" Temp: ", 7);
        s100 = sense_temp / 100;
        if (s100 > 0) {
            lcdDataWrite(s100 + '0');
        }
        s10 = sense_temp / 10 - s100 * 10;
        if (s10 > 0) {
            lcdDataWrite(s10 + '0');
        }
        lcdDataWrite('.');
        lcdDataWrite(sense_temp % 10 + '0');
        lcdDataWrite('C');
    } else if (sense == HUMIDITY) {
        lcdPrintData(" Humi: ", 7);
        s100 = sense_temp / 100;
        if (s100 > 0) {
            lcdDataWrite(s100 + '0');
        }
        s10 = sense_temp / 10 - s100 * 10;
        if (s10 > 0) {
            lcdDataWrite(s10 + '0');
        }
        lcdDataWrite('.');
        lcdDataWrite(sense_temp % 10 + '0');
        lcdDataWrite('%');
    }
}

// 타이머0 오버플로우 인터럽트 서비스 루틴
ISR(TIMER0_OVF_vect) {
    cli(); // 전역 인터럽트 비활성화
    TCNT0 = 112; // 타이머0 카운트 값 재설정
    timer0Cnt++; // 타이머0 카운트 증가
    sei(); // 전역 인터럽트 활성화
}

// INT4 인터럽트 서비스 루틴 (EEPROM 데이터 읽어 UART로 출력)
ISR(INT4_vect) {
    cli(); // 전역 인터럽트 비활성화

    // EEPROM에서 온도/습도 데이터 읽기
    uint8_t read_temp_buf[2];
    uint8_t read_humi_buf[2];

    at25160_Read_Arry(0x0100, read_temp_buf, 2);
    at25160_Read_Arry(0x0200, read_humi_buf, 2);

    // 읽어온 데이터 UART로 출력
    uint16_t read_temp = (read_temp_buf[0] << 8) | read_temp_buf[1];
    uint16_t read_humi = (read_humi_buf[0] << 8) | read_humi_buf[1];

    uart0_put_str("Temp: ");
    uart0_put_int(read_temp);
    uart0_put_str(", Humi: ");
    uart0_put_int(read_humi);
    uart0_put_str("\r\n");

    sei(); // 전역 인터럽트 활성화
}