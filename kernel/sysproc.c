#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
extern int policy;
uint64
sys_exit(void)
{
  int n;
  char buff[32];
  argint(0, &n);
  argstr(1, buff, 32);
  exit(n, buff);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  uint64 n;
  argaddr(0, &p);
  argaddr(1, &n);
  return wait(p, n);
}
uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (killed(myproc()))
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_memsize(void)
{
  return myproc()->sz;
}

uint64
sys_set_ps_priority(void) // we changed the function's signature to int, to return -1 incase of an error
{
  int n;
  argint(0, &n);
  return set_ps_priority(n);
}

uint64
sys_set_cfs_priority(void)
{
  int n;
  argint(0, &n);
  return set_cfs_priority(n);
}

uint64
sys_get_cfs_stats(void)
{
  int pid;
  uint64 pr, rt, st, ret;
  argint(0, &pid);
  argaddr(1, &pr);
  argaddr(2, &rt);
  argaddr(3, &st);
  argaddr(4, &ret);
  return get_cfs_stats(pid, pr, rt, st, ret);
}

uint64
sys_set_policy(void)
{
  int n;
  argint(0, &n);
  if (n < 0 || n > 2)
    return -1;
  policy = n;
  return 0;
}