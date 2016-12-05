#include "../minicrt.h"

int main()
{
    const char* msg = "hello world.";
    int *pa = malloc(32 * 1024 * 1024); //NULL
    int *pb = malloc(1 * 1024 * 1024);
    int *pc = malloc(1 * 1024 * 1024);
    int *pd = malloc(1 * 1024 * 1024);
    free(pc);
    free(pb);
    free(pd);


    fwrite(msg, 1, 12, stdout);
    return 0;
}