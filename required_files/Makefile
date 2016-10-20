KBUILD_CFLAGS += -w
obj-m += birthday.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
unload:
	sudo rmmod birthday
load:
	sudo insmod birthday.ko
clear:
	sudo dmesg -c
view:
	dmesg	
