TARGET = helloRaspberry switch_led device_gpio interrupt led_pwm soft_tone_buzzer hard_tone_buzzer i2c_rgb_led i2c_brightness i2c_rgb_random i2c_rgb_led_switch i2c_servo fnd_cnt fnd_sw_led pir_cnt touchATQT1070 gyro_cnt
LEGACY = -lwiringPi

all : ${TARGET}


${TARGET} : $@ $< ${LEGACY}
# helloRaspberry :
# 	cc -o helloRaspberry helloRaspberry.c 

# switch_led :
# 	cc -o switch_led switch_led.c -lwiringPi
 
clean : 
	rm ${TARGET}
