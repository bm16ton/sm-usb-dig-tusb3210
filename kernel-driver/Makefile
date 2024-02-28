ifneq ($(KERNELRELEASE),)

obj-m := mfd/

else

KDIR ?= /lib/modules/`uname -r`/build

default:
	cd mfd && $(MAKE)
	cp $(PWD)/mfd/Module.symvers $(PWD)/i2c/Module.symvers
	cd i2c && $(MAKE)
#	$(MAKE) -C $(KDIR) M=$(PWD)

endif

.PHONY: clean

clean:
	rm -f mfd/modules.order mfd/Module.symvers mfd/Module.symvers mfd/*.o mfd/*.ko mfd/*.mod.* mfd/*.mod mfd/.*.cmd i2c/modules.order i2c/Module.symvers i2c/*.o i2c/*.ko i2c/*.mod.* i2c/*.mod i2c/.*.cmd modules.order Module.symvers *.o *.ko *.mod.* *.mod

