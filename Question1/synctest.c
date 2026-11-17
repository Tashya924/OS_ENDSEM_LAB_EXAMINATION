#include "types.h"
#include "user.h"

#define CHILDREN 3
#define ROUNDS 5

int
main(void)
{
  int i, j, round;
  int pids[CHILDREN];

  for(i = 0; i < CHILDREN; i++){
    if(sem_init(i, i == 0) < 0){
      printf(2, "synctest: sem_init failed\n");
      exit();
    }
  }

  for(i = 0; i < CHILDREN; i++){
    pids[i] = fork();
    if(pids[i] < 0){
      printf(2, "synctest: fork failed\n");
      for(j = 0; j < i; j++){
        kill(pids[j]);
        sem_post(j);
      }
      for(j = 0; j < i; j++)
        wait();
      exit();
    }
    if(pids[i] == 0){
      for(round = 0; round < ROUNDS; round++){
        if(sem_wait(i) < 0){
          printf(2, "synctest: sem_wait failed\n");
          exit();
        }
        printf(1, "%c%c", 'A' + i,
               round == ROUNDS - 1 && i == CHILDREN - 1 ? '\n' : ' ');
        if(sem_post((i + 1) % CHILDREN) < 0){
          printf(2, "synctest: sem_post failed\n");
          exit();
        }
      }
      exit();
    }
  }

  for(i = 0; i < CHILDREN; i++)
    wait();
  printf(1, "Done\n");
  exit();
}
