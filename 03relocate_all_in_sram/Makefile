PREFIX=arm-linux-gnueabihf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld
AR=$(PREFIX)ar
OBJCOPY=$(PREFIX)objcopy
OBJDUMP=$(PREFIX)objdump

relocate.img : start.S main.c init.c
	$(CC) -nostdlib -g -c -o start.o start.S 
	$(CC) -nostdlib -g -c -o main.o main.c	
	$(CC) -nostdlib -g -c -o init.o init.c
	
	$(LD) -T imx6ull.lds -g start.o  main.o  init.o -o relocate.elf -lgcc -L/home/terry/disk_40g/imx6u/bare/compiler/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4
	
	$(OBJCOPY) -O binary -S relocate.elf  relocate.bin
	$(OBJDUMP) -D -m arm  relocate.elf  > relocate.dis
	../tools/mkimage -n ../tools/imximage.cfg.cfgtmp -T imximage -e 0x80100000 -d ./relocate.bin ./relocate.imx
	dd if=/dev/zero of=1k.bin bs=1024 count=1
	cat 1k.bin relocate.imx > relocate.img

clean:
	rm -f relocate.dis relocate.bin relocate.elf relocate.imx relocate.img *.o


	
