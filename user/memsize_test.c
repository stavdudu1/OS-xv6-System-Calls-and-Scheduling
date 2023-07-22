#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int sizebefore = memsize();
    fprintf(1, "%d \n", sizebefore);
    void *ptr = malloc(20000);
    int sizeafter = memsize();
    fprintf(1, "%d \n", sizeafter);
    free(ptr);
    int sizefree = memsize();
    fprintf(1, "%d \n", sizefree);
    return 0;
}