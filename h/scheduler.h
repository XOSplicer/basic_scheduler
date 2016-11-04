/**
 * File: scheduler.h
 * Author: Felix Stegmaier
 * Created on: 04.11.2016
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


typedef struct proc {
  pid_t pid;
  struct proc *next; /* used to build queues */
} proc_t;

/**
 * Initiate the scheduler
 * Must be called before any process can be created.
 */
void sched_init(void);

/**
 * Create a new process.
 * The process is active, but might not run immediately.
 * If the process could not be created the program terminates.
 *
 * @param  task : a function reference with
 *                void parameters and void return value,
 *                may be null, bun nothing happens.
 *
 * @return      the pid of the created process,
 *              0 if @param task was null
 */
pid_t sched_create_process(void (*task)(void));

/**
 * 
 * @param pid [description]
 */
void sched_kill_process(pid_t pid);

/**
 * [sched_join_process description]
 * @param pid [description]
 */
void sched_join_process(pid_t pid);

/**
 * [sched_pause_process description]
 * @param pid [description]
 */
void sched_pause_process(pid_t pid);

/**
 * [sched_continue_process description]
 * @param pid [description]
 */
void sched_continue_process(pid_t pid);

#endif /* SCHED_H */
