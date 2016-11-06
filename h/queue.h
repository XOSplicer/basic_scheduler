/**
 * File: queue.h
 * Author: Felix Stegmaier
 * Created on: 04.11.2016
 *
 * Functions and types for handeling queues of processes
 * Used by the scheduler
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

/* used to handle processes */
typedef struct proc {
  pid_t pid;
  struct proc *next; /* used to build queues */
} proc_t;

/* used to handle a queue */
typedef struct queue {
  proc_t *first;
  proc_t *last;
} queue_t;

/**
 * create an empty queue
 * @return a reference to an empty queue
 *         used for further handeling of the queue
 *         > 0 if successfull
 */
queue_t* q_create();

/**
 * is q empty
 * @param  q The queue to be checked
 * @return   1 if q is empty
 *           0 if q has at least 1 element
 *           -1 if q is null
 */
int q_is_empty(queue_t* q);

/**
 * insert proc at the end of q
 * will do nothing if q or proc are null
 *
 * @param q    : the queue to insert into
 * @param proc : the process to be inserted
 */
void q_enqueue(queue_t* q, proc_t *proc);

/**
 * pop the front of q, while removing this element from q
 *
 * @param  q : the queue to be popped from
 * @return   the popped element,
 *           null if q is null or empty
 */
proc_t* q_dequeue(queue_t* q);

/**
 * search for an element in q that has pid pid
 * remove this element from q
 * will only remove and return the first appearing element with this pid
 *
 * @param  q   the queue to be searched in
 * @param  pid the pid to be searched for
 * @return     a reference to the now removed element
 *             null if q is null or empty or pid <= 0
 */
proc_t* q_search_and_dequeue(queue_t* q, pid_t pid);

/**
 * check wether q contains pid
 * @param  q   the q to be searched in
 * @param  pid the pid to be searched for
 * @return     1 if an element with pid pid is contained in q
 *             0 else
 */
int q_contains(queue_t* q, pid_t pid);

#endif /* QUEUE_H */
