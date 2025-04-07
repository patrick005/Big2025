//i2c_servo.c
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define RGB_SERVO_I2C_ADDR 0x5e
#define PCA9685_LED_ON_L 0x06
#define PCA9685_PRESCALE 0xFE
#define PCA9685_MODE1 0x00

void i2C_init(int fd, int fre);

int main(void){
    wiringPiSetupGpio();
    int rgb_servo_fd = wiringPiI2CSetup(RGB_SERVO_I2C_ADDR);
    i2C_init(rgb_servo_fd, 0x79); // 주파수 50Hz 설정 20ms 
    // 프리스케일값 = (오실러레이터 주파수 / (4096 * 원하는 주파수)) - 1
    // 2500000 / ( 4096 * ( 0x79 + 1)) = 50.028817
    
    // int servo_0 = 120;
    // int servo_180 = 500;
    int servo_0 = 100; //90도는 380정도이다;; 300이 아니었다...
    int servo_180 = 500;
// for(int k=0; k<3; k++){
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 12, 0); //servo1 on_off
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 14, servo_0); //servo1 pwm duty
    delay(10);
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 16, 0); //servo2 on_off
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 18, servo_0); //servo2 pwm duty
    delay(800);

    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 14, servo_180/2); //servo1 pwm duty
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 18, servo_180/2); //servo2 pwm duty
    delay(800);

    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 14, servo_180); //servo1 pwm duty
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 18, servo_180); //servo2 pwm duty
    delay(800);
// }
    //free: 전압이 계속 흘러서 무리가 갈수 있으니 해제도 해주기
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 12, 0); //servo1 on_off
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 14, 0); //servo1 on_off
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 16, 0); //servo2 on_off
    wiringPiI2CWriteReg16(rgb_servo_fd, PCA9685_LED_ON_L + 18, 0); //servo2 on_off
    
    return 0;
}


void i2C_init(int fd, int freq){
    
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0x10);    // 리셋
    delay(10);                                        // 리셋 후 대기
    wiringPiI2CWriteReg8(fd, PCA9685_PRESCALE, freq); // 주파수 60Hz 설정
    wiringPiI2CWriteReg8(fd, PCA9685_MODE1, 0xA1);
}