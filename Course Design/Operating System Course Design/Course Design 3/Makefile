ifneq ($(KERNELRELEASE),)
	obj-m := myModule.o
else
	PWD := $(shell pwd)
	KVER:= $(shell uname -r)
	KDIR:= /lib/modules/$(KVER)/build
modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
clean:
	rm -rf *.o *.ko .tmp_versions *.mod.c *.order *.symvers
endif