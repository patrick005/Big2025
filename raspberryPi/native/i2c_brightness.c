//i2c_brightness.c
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define RGB_SERVO_I2C_ADDR 0x5e
#define PCA9685_LED_ON_L 0x06
#define PCA9685_PRESCALE 0xFE
#define PCA9685_MODE1 0x00

void i2C_init(int fd, int fre);

int main(void){
    
    int rgb_servo_fd = wiringPiI2CSetup(RGB_SERVO_I2C_ADDR);
    i2C_init(rgb_servo_fd, 0x79); // 주파수 50Hz 설정
    // 프리스케일값 = (오실러레이터 주파수 / (4096 * 원하는 주파수)) - 1
    // 2500000 / ( 4096 * ( 0x79 + 1)) = 50.028817
    
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L, 0); //빨간색
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L+4, 0); //녹색
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L+8, 0); //퍼런색
    
    // //빨간색
    // wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 2, 4095);
    // delay(1000);
    // wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 2, 0);
    // delay(1000);

    // //녹색
    // wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 6, 4095);
    // delay(1000);
    // wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 6, 0);
    // delay(1000);

    // //파란색
    // wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 10, 4095);
    // delay(1000);
    // wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 10, 0);
    // delay(1000);

    // 점점 밝아지는 코드
    for (int i = 0; i < 4096; i++){
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 2, i);
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 6, 4096 - i);
        wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 10, (i * 2) % 4006);
        delay(1);
        
    }
    

    return 0;
}


void i2C_init(int fd, int freq){
    
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0x01);    // 리셋
    delay(10);                                        // 리셋 후 대기
    wiringPiI2CWriteReg8(fd, PCA9685_PRESCALE, freq); // 주파수 60Hz 설정
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0xA1);
    

}