ifneq ($(KERNELRELEASE),)
obj-m := ti-smusbdig.o

else


KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR)  M=$(PWD)
	cd ../
endif

.PHONY: clean

clean:
	rm -f modules.order Module.symvers *.o *.ko *.mod.* *.mod

