#include "types.h"
#include "user.h"

int global = 1;

int
main(void)
{
  int gate[2], pid, va;
  char ready = 1;

  printf(1, "Free pages at startup: %d\n", freepages());
  if(sbrk(10 * 4096) == (char*)-1){
    printf(2, "memtest: sbrk failed\n");
    exit();
  }
  printf(1, "Free pages after sbrk: %d\n", freepages());

  va = (int)&global;
  printf(1, "Global variable: VA 0x%x, PA 0x%x\n", va, va2pa(va));
  printf(1, "va2pa(0x7FFFFFFF) = %d\n", va2pa(0x7FFFFFFF));

  if(pipe(gate) < 0){
    printf(2, "memtest: pipe failed\n");
    exit();
  }
  printf(1, "Free pages before fork: %d\n", freepages());
  pid = fork();
  if(pid < 0){
    printf(2, "memtest: fork failed\n");
    exit();
  }
  if(pid == 0){
    close(gate[1]);
    if(read(gate[0], &ready, 1) == 1)
      printf(1, "Child global: VA 0x%x, PA 0x%x\n", va, va2pa(va));
    close(gate[0]);
    exit();
  }

  printf(1, "Free pages after fork: %d\n", freepages());
  printf(1, "Parent global: VA 0x%x, PA 0x%x\n", va, va2pa(va));
  if(write(gate[1], &ready, 1) != 1)
    printf(2, "memtest: pipe write failed\n");
  close(gate[1]);

  if(wait() == pid)
    printf(1, "Free pages after wait: %d\n", freepages());
  else
    printf(2, "memtest: wait failed\n");
  close(gate[0]);
  exit();
}
