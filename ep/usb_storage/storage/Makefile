#
# Makefile for the USB Mass Storage device drivers.
#
# 15 Aug 2000, Christoph Hellwig <hch@infradead.org>
# Rewritten to use lists instead of if-statements.
#

#ccflags-y := -Idrivers/scsi

#obj-m		+= uas.o
obj-m	+= usb-storage.o

usb-storage-y := scsiglue.o protocol.o transport.o usb.o
usb-storage-y += initializers.o sierra_ms.o option_ms.o
usb-storage-y += usual-tables.o
usb-storage-m += debug.o

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
	find . -type f -name "*~" -o -name "*.o"  -o -name "*.cmd" -o -name "*.mod.c"  -o -name "*.o.ur-safe"  |  xargs rm -rf

clean:
	rm -rf *~ .tmp_versions modules.order Module.symvers
	find . -type f -name "*~" -o -name "*.o" -o -name "*.ko" -o -name "*.cmd" -o -name "*.mod.c"   -o -name "*.o.ur-safe" |  xargs rm -rf
