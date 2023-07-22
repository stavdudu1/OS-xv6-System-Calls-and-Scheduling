#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int arg = atoi(argv[0]);
    printf("%d\n", set_policy(arg));
    exit(0, "byeeee\n");
}