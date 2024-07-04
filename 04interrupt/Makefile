PREFIX=arm-linux-gnueabihf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld
AR=$(PREFIX)ar
OBJCOPY=$(PREFIX)objcopy
OBJDUMP=$(PREFIX)objdump

INCLUDEDIR 	:= $(shell pwd)/include
CFLAGS 		:= -Wall
CPPFLAGS   	:= -nostdinc -fno-builtin -I$(INCLUDEDIR)
LDFLAGS         := -L/home/terry/disk_40g/imx6u/bare/compiler/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4 -lgcc
objs :=  start.o main.o led.o  eabi_compat.o  gic.o

TARGET := except

$(TARGET).img : $(objs)
	$(LD) -T imx6ull.lds -o $(TARGET).elf $^ $(LDFLAGS)
	$(OBJCOPY) -O binary -S $(TARGET).elf  $(TARGET).bin
	$(OBJDUMP) -D -m arm  $(TARGET).elf  > $(TARGET).dis	
	../tools/mkimage -n ../tools/imximage.cfg.cfgtmp -T imximage -e 0x80100000 -d $(TARGET).bin $(TARGET).imx
	dd if=/dev/zero of=1k.bin bs=1024 count=1
	cat 1k.bin $(TARGET).imx > $(TARGET).img

%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET).dis  $(TARGET).bin $(TARGET).elf $(TARGET).imx $(TARGET).img *.o


	
