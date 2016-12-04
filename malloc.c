#include "minicrt.h"

typedef struct _heap_header
{
    enum {
        HEAP_BLOCK_FREE = 0xABABABAB,
        HEAP_BLOCK_USED = 0xCDCDCDCD,
    } type;
    unsigned size;
    struct _heap_header *next;
    struct _head_header *prev;
} heap_header;

#define ADDR_ADD(a, o) (((char*)(a)) + o)
#define HEADER_SIZE (sizeof(heap_header))

static heap_header* list_head = NULL;

void free(void* ptr)
{

}

void* malloc(unsigned size)
{
    return NULL;
}

static int brk(void* end_data_segment)
{
    int ret = 0;
    //brk system call number: 45
    asm("movl $45, %%eax    \n\t"
        "movl %1, %%ebx     \n\t"
        "int $0x80          \n\t"
        "movl %%eax, %0     \n\t"
        : "=r"(ret): "m"(end_data_segment));
}

int mini_crt_heap_init()
{
    void* base = NULL;
    heap_header *header = NULL;
    unsigned heap_size = 1024*1024*32;
    base = (void*)brk(0);
    void* end = ADDR_ADD(base, heap_size);
    end = (void*)brk(end);
    if(!end)
        return 0;

    header = (heap_header*)base;
    header->size = heap_size;
    header->type = HEAP_BLOCK_FREE;
    header->next = NULL;
    header->prev = NULL;

    list_head = header;
    return 1;
}