#include <stdlib.h>
#include <stdio.h>

#include "scheduler.h"

void task1(void) {
  for (size_t i = 0; i < 100; i++) {
    printf("Task 1: %lu\n", i);
    usleep(1000);
  }
}

void task2(void) {
  for (size_t i = 0; i < 100; i++) {
    printf("Task 2: %lu\n", i);
    usleep(1000);
  }
}

void task3(void) {
  for (size_t i = 0; i < 100; i++) {
    printf("Task 3: %lu\n", i);
    usleep(1000);
  }
}

int main(int argc, char const *argv[]) {
  pid_t t1, t2, t3;
  sched_init();
  t1 = sched_create_process(task1);
  t2 = sched_create_process(task2);
  t3 = sched_create_process(task3);
  usleep(10000);
  //sched_pause_process(t2);
  //sched_kill_process(t3);
  sched_join_process(t1);
  //sched_continue_process(t2);
  sched_join_process(t2);

  return 0;
}
