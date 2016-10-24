#include <stdlib.h>
#include <stdio.h>

#include "scheduler.h"

void task1(void) {
  while(1) {
    printf("Task 1\n");
    usleep(1000);
  }
}

void task2(void) {
  while(1) {
    printf("Task 2\n");
    usleep(1000);
  }
}

void task3(void) {
  while(1) {
    printf("Task 3\n");
    usleep(1000);
  }
}

int main(int argc, char const *argv[]) {
  sched_init();
  sched_create_process(task1);
  sched_create_process(task2);
  sched_create_process(task3);
  while (1) {

  }
  return 0;
}
