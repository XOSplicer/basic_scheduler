/**
 * File: tests.c
 * Author: Felix Stegmaier
 * Created on: 04.11.2016
 */

#include "../h/tests.h"

void task1(void) {
  for (size_t i = 0; i <= 10; i++) {
    printf("\tTask 1: %lu\n", i);
    usleep(COUNT_DELAY);
  }
}

void task2(void) {
  for (size_t i = 0; i <= 10; i++) {
    printf("\tTask 2: %lu\n", i);
    usleep(COUNT_DELAY);
  }
}

void task3(void) {
  for (size_t i = 0; i <= 10; i++) {
    printf("\tTask 3: %lu\n", i);
    usleep(COUNT_DELAY);
  }
}

void test1(void) {
  pid_t t1, t2, t3;

  t1 = sched_create_process(task1);
  printf("Created task 1\n");

  t2 = sched_create_process(task2);
  printf("Created task 2\n");

  t3 = sched_create_process(task3);
  printf("Created task 3\n");

  sched_join_process(t1);
  printf("Joined task 1\n");

  sched_join_process(t2);
  printf("Joined task 2\n");

  sched_join_process(t3);
  printf("Joined task 3\n");
}

void test2(void) {
  pid_t t1, t2, t3;

  t1 = sched_create_process(task1);
  printf("Created task 1\n");

  t2 = sched_create_process(task2);
  printf("Created task 2\n");

  t3 = sched_create_process(task3);
  printf("Created task 3\n");

  sched_pause_process(t1);
  printf("Paused task 1\n");

  sched_join_process(t2);
  printf("Joined task 2\n");

  sched_join_process(t3);
  printf("Joined task 3\n");

  sched_continue_process(t1);
  printf("Continued task 1\n");

  sched_join_process(t1);
  printf("Joined task 1\n");
}

void test3(void) {
  pid_t t1, t2, t3;

  t1 = sched_create_process(task1);
  printf("Created task 1\n");

  t2 = sched_create_process(task2);
  printf("Created task 2\n");

  t3 = sched_create_process(task3);
  printf("Created task 3\n");

  sched_pause_process(t1);
  printf("Paused task 1\n");

  sched_kill_process(t2);
  printf("Killed task 2\n");

  sched_continue_process(t1);
  printf("Continued task 1\n");

  sched_join_process(t1);
  printf("Joined task 1\n");

  sched_join_process(t2);
  printf("Joined task 2\n");
}

void test4(void) {
  pid_t t1, t2, t3;

  t1 = sched_create_process(task1);
  printf("Created task 1\n");

  t2 = sched_create_process(task2);
  printf("Created task 2\n");

  t3 = sched_create_process(task3);
  printf("Created task 3\n");

  sched_kill_process(t1);
  printf("Killed task 1\n");

  sched_kill_process(t2);
  printf("Killed task 2\n");

  sched_kill_process(t3);
  printf("Killed task 3\n");
}
