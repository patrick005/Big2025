//i2c_rgb_led_switch.c
// 스위치 1,2,3을 이용해서
// 1 -> R 색 변화
// 2-> G 색 변화
// 3-> B 색변화
// 스위치를 오래 누르면 높은 값으로 변화 할 수 있게 만들기


#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>


// gpio pin (물리핀이 아닌 gpio핀 설정임)
#define SW1 4
#define SW2 17
#define SW3 27

#define RGB_SERVO_I2C_ADDR 0x5e
#define PCA9685_LED_ON_L 0x06
#define PCA9685_PRESCALE 0xFE
#define PCA9685_MODE1 0x00

void i2C_init(int fd, int fre);

void SW_ISR1(void);
void SW_ISR2(void);
void SW_ISR3(void);


int main(){

    int rgb_servo_fd = wiringPiI2CSetup(RGB_SERVO_I2C_ADDR);
    i2C_init(rgb_servo_fd, 0x79); // 주파수 50Hz 설정
    
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L, 0); //빨간색
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L+4, 0); //녹색
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L+8, 0); //퍼런색
    
    int sw[4] = { SW1, SW2, SW3};
    wiringPiISR(SW1, INT_EDGE_RISING, /*&*/SW_ISR1);// 저거 붙이나 안붙이나 똑같지만 포인터로 넣어야해서 넣는게 맞는표현
    wiringPiISR(SW2, INT_EDGE_RISING, /*&*/SW_ISR2);
    wiringPiISR(SW3, INT_EDGE_RISING, /*&*/SW_ISR3);
    
    // for(int i = 0; i<4; ++i){
    //     pinMode(led[i], OUTPUT);
    //     pinMode(sw[i], INPUT);
    // }

    while(1){

    }
        return 0;
}

void SW_ISR1(void){
    for (int i = 0; i < 4096; i++){
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 2, i);
        delay(1);  
    }

}
void SW_ISR2(void){
    for (int i = 0; i < 4096; i++){
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 6, 4096 - i);
        delay(1);
    }

}
void SW_ISR3(void){
    for (int i = 0; i < 4096; i++){
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 10, i);
        delay(1);
    }
}


void i2C_init(int fd, int freq){
    
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0x01);    // 리셋
    delay(10);                                        // 리셋 후 대기
    wiringPiI2CWriteReg8(fd, PCA9685_PRESCALE, freq); // 주파수 60Hz 설정
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0xA1);
    

}