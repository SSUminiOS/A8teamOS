#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_CHILD  5
#define NUM_LOOP   5

// ret: 0: child, 1: parent
int create_child(void) {
  for (int i = 0; i < NUM_CHILD; i++) {
    int pid = fork();
    if (pid == 0) {
      sleep(10);
      return 0;
    }
  }
  return 1;
}

void exit_child(int parent) {
  if (parent)
    while (wait() != -1); // wait for all child processes to finish
  else
    exit();
}

int main(int argc, char **argv) {
  int p; // is this parent?
  
  printf(1, "FCFS test start\n");

  // Test 1
  printf(1, "\n자식 프로세스를 5번 실행\n");
  
  p = create_child();

  for (int i = 0; i < NUM_LOOP; i++) {
    if (p == 0)
      printf(1, " process %d ", getpid());
  }
  printf(1, "\n");

  exit_child(p);

  // Test 2
  printf(1, "\n루프돌며 자신 PID 출력하고 CPU 양보\n");

  p = create_child();

  for (int i = 0; i < NUM_LOOP; i++) {
    if (p == 0) {
      printf(1, " process %d ", getpid());
      yield();
    }
  }
   printf(1, "\n");

  exit_child(p);

  // Test 3
  printf(1, "\n자신 PID 출력하고 1초 대기\n");

  p = create_child();

  for (int i = 0; i < NUM_LOOP; i++) {
    if (p == 0) {
      printf(1, " process %d \n", getpid());
      sleep(1);
    }
  }

  exit_child(p);


   exit();
}
