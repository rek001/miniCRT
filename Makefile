all:
	gcc -m32 -fno-builtin -nostdlib -fno-stack-protector -c *.c
	ar -rs minicrt.a *.o

clean:
	rm -rf *.o
	rm -rf *.a
