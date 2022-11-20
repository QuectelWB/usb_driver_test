

obj-$(CONFIG_USB_SERIAL)			+= usbserial.o

usbserial-y := usb-serial.o generic.o bus.o

obj-$(CONFIG_USB_SERIAL_OPTION)			+= option.o
obj-$(CONFIG_USB_SERIAL_WWAN)			+= usb_wwan.o


PWD := $(shell pwd)

ifeq ($(ARCH),)
ARCH := $(shell uname -m)
endif
ifeq ($(CROSS_COMPILE),)
CROSS_COMPILE :=
endif
ifeq ($(KDIR),)
KDIR := /lib/modules/$(shell uname -r)/build
ifeq ($(ARCH),i686)
ifeq ($(wildcard $KDIR/arch/$ARCH),)
ARCH=i386
endif
endif
endif

ifneq ($(findstring &,${PWD}),)
$(warning "${PWD}")
$(warning "current directory contain special char '&' !")
$(error "please remove it!")
endif

default:
	$(MAKE) ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} -C $(KDIR) M=$(PWD) modules
	rm -rf *~ .tmp_versions modules.order Module.symvers
	find . -type f -name "*~" -o -name "*.o" -o  -name "*.cmd" -o -name "*.mod.c"  -o -name "*o.ur-detected" -o -name ".cache.mk"|  xargs rm -rf

clean:
	rm -rf *~ .tmp_versions modules.order Module.symvers
	find . -type f -name "*~" -o -name "*.o" -o -name "*.ko" -o -name "*.cmd" -o -name "*.mod.c"  -o -name "*o.ur-detected" -o -name ".cache.mk"|  xargs rm -rf
