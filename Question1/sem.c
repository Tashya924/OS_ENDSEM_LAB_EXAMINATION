#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"

#define NSEM 8

struct semaphore {
  int value;
  int inuse;
};

static struct spinlock semlock;
static struct semaphore semaphores[NSEM];

void
seminit(void)
{
  initlock(&semlock, "semaphores");
}

int
sem_init(int id, int value)
{
  struct semaphore *sem;

  if(id < 0 || id >= NSEM || value < 0)
    return -1;

  sem = &semaphores[id];
  acquire(&semlock);
  sem->value = value;
  sem->inuse = 1;
  if(value > 0)
    wakeup(sem);
  release(&semlock);
  return 0;
}

int
sem_wait(int id)
{
  struct semaphore *sem;

  if(id < 0 || id >= NSEM)
    return -1;

  sem = &semaphores[id];
  acquire(&semlock);
  if(!sem->inuse){
    release(&semlock);
    return -1;
  }
  while(sem->value == 0){
    if(myproc()->killed){
      release(&semlock);
      return -1;
    }
    sleep(sem, &semlock);
  }
  sem->value--;
  release(&semlock);
  return 0;
}

int
sem_post(int id)
{
  struct semaphore *sem;

  if(id < 0 || id >= NSEM)
    return -1;

  sem = &semaphores[id];
  acquire(&semlock);
  if(!sem->inuse || sem->value == __INT_MAX__){
    release(&semlock);
    return -1;
  }
  sem->value++;
  wakeup(sem);
  release(&semlock);
  return 0;
}
