# If called directly from the command line, invoke the kernel build system.
ifeq ($(KERNELRELEASE),)

    KERNEL_SOURCE := /usr/src/linux-4.2.0
    PWD := $(shell pwd)
default: module query_app
query_app: ioctl_app.c
	gcc -o  query_app ioctl_app.c
module:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) clean
	${RM} query_app

# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
else

    obj-m := query_ioctl.o

endif
