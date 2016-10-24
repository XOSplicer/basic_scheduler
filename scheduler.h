#ifndef SCHED_H
#define  SCHED_H

/* time each slot for a process is long in microseconds */
#define QUANTUM 10000UL  /* 10 milliseconds*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


typedef struct proc {
  pid_t pid;
  struct proc *next;
} proc_t;

void sched_init(void);

pid_t sched_create_process(void (*task)(void));

void sched_kill_process(pid_t pid);

//void sched_join_process(pid_t pid);

#endif /* SCHED_H */
