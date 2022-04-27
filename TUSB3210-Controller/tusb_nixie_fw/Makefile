tfirm.bin :	tfirm.ihx
		hex2bin tfirm.ihx

tfirm.ihx :	tfirm.rel usbiofun.rel
		sdcc --noloopreverse tfirm.rel usbiofun.rel
tfirm.rel:	tfirm.c usbiofun.c usbiofun.h commands.h
		sdcc -c --noloopreverse tfirm.c

usbiofun.rel:	usbiofun.c usbiofun.h commands.h
		sdcc -c --noloopreverse usbiofun.c

clean	:
		rm -f *.ihx *.map *.rst *.lnk *.asm *.lst *.rel *.sym *.mem

