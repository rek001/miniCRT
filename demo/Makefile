all:
	gcc -m32 -fno-builtin -c main.c -o main.o
	ld main.o ../minicrt.a -m elf_i386 -static -e mini_crt_entry -o main
clean:
	rm -rf *.o
	rm -rf main