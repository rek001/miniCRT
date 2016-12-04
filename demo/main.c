#include "../minicrt.h"

int main()
{
    int *pa = malloc(32 * 1024 * 1024); //NULL
    int *pb = malloc(1 * 1024 * 1024);
    int *pc = malloc(1 * 1024 * 1024);
    int *pd = malloc(1 * 1024 * 1024);
    free(pc);
    free(pa);
    free(pd);
    return 0;
}