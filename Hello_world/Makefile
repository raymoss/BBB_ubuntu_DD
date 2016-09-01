obj-m := hello.o
KERNEL_SOURCE := /home/ray/BBB_kernel_4.1.20/bb-kernel/KERNEL/
PWD := $(shell pwd)
CCC := /home/ray/cross_compiler_BBB/bin
default:
	${MAKE} ARCH=arm CROSS_COMPILE=${CCC}/arm-linux-gnueabihf- -C ${KERNEL_SOURCE} SUBDIRS=${PWD} modules

clean:
	${MAKE} ARCH=arm CROSS_COMPILE=${CCC}/arm-linux-gnueabihf- -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
