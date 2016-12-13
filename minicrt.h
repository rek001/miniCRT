#ifndef __MINI_CRT_H__
#define  __MINI_CRT_H__

//stdlib
void exit(int exitcode);

//string
int strcmp(const char *src, const char *dst);

char *itoa(int n, char *str, int radix);

char *strcpy(char *dest, const char *src);

unsigned strlen(const char *str);

//heap
#ifndef NULL
#define NULL (0)
#endif

void free(void *ptr);

void *malloc(unsigned size);

int mini_crt_heap_init();

//IO
typedef int FILE;  //no buffer
#define EOF (-1)
#define stdin ((FILE*)0)
#define stdout ((FILE*)1)
#define stderr ((FILE*)2)

int mini_crt_io_init();

/*1. 仅实现基本的文件操作，不带缓冲机制*/
FILE *fopen(const char *filename, const char *mode);

int fread(void *buffer, int size, int count, FILE *stream);

int fwrite(const void *buffer, int size, int count, FILE *stream);

int fclose(FILE *fp);

int fseek(FILE *fp, int offset, int set);

//printf
int fputc(int c, FILE *stream);

int fputs(const char *str, FILE *stream);

int printf(const char *format, ...);

int fprintf(FILE *stream, const char *format, ...);


//atexit
typedef void(*atexit_func_t)(void);

int atexit(atexit_func_t func);

#endif  //__MINI_CRT_H__