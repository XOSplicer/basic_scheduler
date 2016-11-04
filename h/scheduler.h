/**
 * File: scheduler.h
 * Author: Felix Stegmaier
 * Created on: 04.11.2016
 *
 * Functions to handle processes.
 * Schould only called by the main program that is control
 * over the handeled processes.
 *
 */

#ifndef SCHED_H
#define SCHED_H

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
#include "queue.h"


/* used to handle processes */
typedef struct proc {
  pid_t pid;
  struct proc *next; /* used to build queues */
} proc_t;

/**
 * Initiate the scheduler
 * Must be called before any process can be created.
 * Multiple calls have no effect.
 */
void sched_init(void);

/**
 * Create a new process.
 * The process is active, but might not run immediately.
 * If the process could not be created the program terminates.
 *
 * @param task : a function reference with
 *               void parameters and void return value,
 *               may be null, bun nothing happens.
 *
 * @return the pid of the created process,
 *         0 if @param task was null
 */
pid_t sched_create_process(void (*task)(void));

/**
 * Kill a process (i.e. terminate it immediately).
 * Will do nothing if the pid is not valid.
 *
 * @param pid : The pid of the process to be killed
 */
void sched_kill_process(pid_t pid);

/**
 * Wait blocking for a process.
 * If the pid is invalid or the process already finished
 * this will continue.
 *
 * @param pid : The pid of the process to join
 */
void sched_join_process(pid_t pid);

/**
 * Pause a process (i.e. suspend it).
 * The process can be continued with sched_continue_process(pid);
 * Will do nothing if the pid is invalid or the process is already paused
 *
 * @param pid : The pid of the process to be paused
 */
void sched_pause_process(pid_t pid);

/**
 * Continue a previosly paused process (i.e. make it aktive again).
 * Will do nothing if the pid is invalid or the process is already active.
 *
 * @param pid : The pid of the process to be continued
 */
void sched_continue_process(pid_t pid);

#endif /* SCHED_H */
