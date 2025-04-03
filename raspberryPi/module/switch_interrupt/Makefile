CC = gcc
obj-m := switch_interrupt.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean



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
