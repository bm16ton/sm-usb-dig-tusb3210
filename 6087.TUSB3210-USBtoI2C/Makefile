#i2c-usb.bin :	tfirm.ihx
#		hex2bin tfirm.ihx

#tfirm.ihx :	tfirm.rel usbiofun.rel
#		sdcc --noloopreverse tfirm.rel usbiofun.rel
t2c-usb.rel:	main.c descrip.c eeprom.c  i2c.c pec.c usb.c usbinit.c REG52modified.H tusb2136.h Types.h usb.h
		sdcc -c --noloopreverse main.c

#usbiofun.rel:	usbiofun.c usbiofun.h commands.h
#		sdcc -c --noloopreverse usbiofun.c

clean	:
		rm -f *.ihx *.map *.rst *.lnk *.asm *.lst *.rel *.sym *.mem

