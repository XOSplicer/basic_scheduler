#ifndef SCHED_H
#define  SCHED_H

/* time each slot for a process is long in microseconds */
#define QUANTUM 10000UL  /* 10 milliseconds*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


typedef struct proc {
  pid_t pid;
  struct proc *next;
} proc_t;

void sched_init(void);

pid_t sched_create_process(void (*task)(void));

void sched_kill_process(pid_t pid);

void sched_join_process(pid_t pid);

void sched_pause_process(pid_t pid);

void sched_continue_process(pid_t pid);

#endif /* SCHED_H */
