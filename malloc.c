#include "minicrt.h"

typedef struct _heap_header {
    enum {
        HEAP_BLOCK_FREE = 0xABABABAB,
        HEAP_BLOCK_USED = 0xCDCDCDCD,
    } type;
    unsigned size;
    struct _heap_header *next;
    struct _heap_header *prev;
} heap_header;

#define ADDR_ADD(a, o) (((char*)(a)) + o)
#define HEADER_SIZE (sizeof(heap_header))

static heap_header *list_head = NULL;

void free(void *ptr) {
    heap_header *header = (heap_header*)NULL;
    header = (heap_header *) (ADDR_ADD(ptr, -HEADER_SIZE));
    if (header->type != HEAP_BLOCK_USED) {
        return;
    }
    header->type = HEAP_BLOCK_FREE;
    if (header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE) {
        //merge prev
        header->prev->next = header->next;
        header->prev->size += header->size;
        if (header->next != NULL) {
            header->next->prev = header->prev;
        }
        header = header->prev;
    }
    if (header->next != NULL && header->next->type == HEAP_BLOCK_FREE) {
        //merge next
        header->next->prev = header->prev;
        header->next->size += header->size;
        if (header->prev != NULL) {
            header->prev->next = header->next;
        }
    }
}

void *malloc(unsigned size) {
    heap_header *header = (heap_header*)NULL;
    if (size == 0) {
        return NULL;
    }
    header = list_head;
    while (header != NULL) {
        if (header->type == HEAP_BLOCK_USED) {
            header = header->next;
            continue;
        }
        if (header->size > size + HEADER_SIZE && header->size < size + HEADER_SIZE * 2) {
            header->type = HEAP_BLOCK_USED;
        } else if (header->size > size + HEADER_SIZE * 2) {
            //split
            heap_header *next = (heap_header *) ADDR_ADD(header, size + HEADER_SIZE);
            next->prev = header;
            next->next = header->next;
            next->type = HEAP_BLOCK_FREE;
            next->size = header->size - size - HEADER_SIZE;
            header->next = next;
            header->size = size + HEADER_SIZE;
            header->type = HEAP_BLOCK_USED;
            return ADDR_ADD(header, HEADER_SIZE);
        }
        header = header->next;
    }
    return NULL;
}

static int brk(void *end_data_segment) {
    int ret = 0;
    //brk system call number: 45
    asm("movl $45, %%eax    \n\t"
            "movl %1, %%ebx     \n\t"
            "int $0x80          \n\t"
            "movl %%eax, %0     \n\t"
    : "=r"(ret): "m"(end_data_segment));
}

//1号系统调用号，从数据段结束地址向后调整32M作为堆空间，之后不再扩展或者缩小
int mini_crt_heap_init() {
    void *base = NULL;
    heap_header *header = NULL;
    unsigned heap_size = 1024 * 1024 * 32;  //32M
    base = (void *) brk(0);
    void *end = ADDR_ADD(base, heap_size);
    end = (void *) brk(end);
    if (!end)
        return 0;

    header = (heap_header *) base;
    header->size = heap_size;
    header->type = HEAP_BLOCK_FREE;
    header->next = NULL;
    header->prev = NULL;

    list_head = header;
    return 1;
}