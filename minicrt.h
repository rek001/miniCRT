#ifndef __MINI_CRT_H__
#define  __MINI_CRT_H__

//string
int strcmp(const char* src, const char *dst);

//heap
#ifndef NULL
#define NULL (0)
#endif
void free(void *ptr);
void* malloc(unsigned size);
static int brk(void* end_data_segment);
int mini_crt_init_heap();

//IO
typedef int FILE;  //no buffer
#define EOF (-1)
#define stdin ((FILE*)0)
#define stdout ((FILE*)1)
#define stderr ((FILE*)2)
int mini_crt_io_init();
FILE* fopen(const char* filename, const char* mode);
int fread(void* buffer, int size, int count, FILE* stream);
int fwrite(const void* buffer, int size, int count, FILE* stream);
int fclose(FILE* fp);
int fseek(FILE* fp, int offset, int set);

//atexit
typedef void(*atexit_func_t)(void);
int atexit(atexit_func_t func);

#endif  //__MINI_CRT_H__