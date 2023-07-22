#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int i;
    int pid;
    set_policy(2);

    for (i = 0; i < 15; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            int c_pid = getpid();
            set_cfs_priority(i % 3);
            int j;
            for (j = 1; j <= 100000000; j++)
            {
                if (j % 1000000 == 0)
                {
                    sleep(1);
                }
            }

            sleep(10 * i);
            char *pr = "a";
            char *rt = "b";
            char *st = "c";
            char *ret = "d";

            get_cfs_stats(c_pid, pr, rt, st, ret);
            printf("pid: %d priority: %s rtime: %s stime: %s retime: %s\n", c_pid, pr, rt, st, ret);

            break;
        }
    }
    if (pid != 0)
    {
        for (i = 0; i < 15; i++)
        {
            sleep(5);
            wait(0, 0);
        }
    }
    return 0;
}
