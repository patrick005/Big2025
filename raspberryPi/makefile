TARGET = helloRaspberry switch_led


all : ${TARGET}

helloRaspberry :
	cc -o helloRaspberry helloRaspberry.c -lwiringPi

switch_led :
	cc -o switch_led switch_led.c -lwiringPi
 
clean : 
	rm ${TARGET}
