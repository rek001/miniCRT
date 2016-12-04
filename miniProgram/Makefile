all:
	gcc -m32 -fno-builtin -c miniprogram.c -o miniprogram.o
	ld miniprogram.o -m elf_i386 -static -e nomain -o miniprogram
clean:
	rm -rf *.o
	rm -rf miniprogram