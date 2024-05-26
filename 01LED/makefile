led.bin:led.s
	arm-linux-gnueabihf-gcc -g -c led.s -o led.o
	arm-linux-gnueabihf-ld -Ttext 0X87800000 led.o -o led.elf 
	arm-linux-gnueabihf-objcopy -O binary -S -g led.elf led.bin
# 反汇编有 —S 参数的二进制文件
	arm-linux-gnueabihf-objdump -D -b binary -m arm led.bin > led.txt
# 返回边elf 文件
	arm-linux-gnueabihf-objdump -D led.elf > led.dis

# 反汇编没有 ——S 参数的二进制文件
	arm-linux-gnueabihf-objcopy -O binary  -g led.elf ledns.bin
	arm-linux-gnueabihf-objdump -D -b binary -m arm ledns.bin > ledns.txt

clean:
	rm -rf *.o led.bin led.elf led.dis led.txt ledns.txt ledns.bin
	
	
