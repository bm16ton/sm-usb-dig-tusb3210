ifneq ($(KERNELRELEASE),)
obj-m := i2c-ti-smusbdig.o

else


KDIR ?= /lib/modules/`uname -r`/build
export KBUILD_EXTRA_SYMBOLS=$(PWD)/Module.symvers

default:
	$(MAKE) -C $(KDIR) M=$(PWD)

endif

.PHONY: clean

clean:
	rm -f modules.order Module.symvers *.o *.ko *.mod.* *.mod

