CC = gcc
obj-m := led_module.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -f *.ko
	rm -f *.o
	rm -f *.mod.*
	rm -f .*.cmd


# TARGET = helloRaspberry switch_led device_gpio interrupt
# LEGACY = -lwiringPi

# all : ${TARGET}


# ${TARGET} : $@ $< ${LEGACY}
# # helloRaspberry :
# # 	cc -o helloRaspberry helloRaspberry.c 

# # switch_led :
# # 	cc -o switch_led switch_led.c -lwiringPi
 
# clean : 
# 	rm ${TARGET}
