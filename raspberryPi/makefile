TARGET = helloRaspberry switch_led device_gpio interrupt
LEGACY = -lwiringPi

all : ${TARGET}


${TARGET} : $@ $< ${LEGACY}
# helloRaspberry :
# 	cc -o helloRaspberry helloRaspberry.c 

# switch_led :
# 	cc -o switch_led switch_led.c -lwiringPi
 
clean : 
	rm ${TARGET}
