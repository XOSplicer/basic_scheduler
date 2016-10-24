#include "scheduler.h"

proc_t *curr_proc;
proc_t *first_proc;
proc_t *last_proc;

proc_t *pop_proc_queue() {
  if(!first_proc) {
    /* empty queue */
    fprintf(stderr,"No member in queue!\n");
    return NULL;
  } else if(first_proc == last_proc) {
    proc_t *temp = first_proc;
    first_proc = NULL;
    last_proc = NULL;
    return temp;
  } else {
    proc_t *temp = first_proc;
    first_proc = first_proc->next;
    return temp;
  }
}

void append_proc_queue(proc_t* proc) {
  if(!first_proc) {
    /* empty queue */
    first_proc = proc;
    last_proc = proc;
    last_proc->next = NULL;
  } else {
    last_proc->next = proc;
    last_proc = last_proc->next;
    last_proc->next = NULL;
  }
}

void sigalrm_handler(int sig) {
  printf("Scheduler called by interrupt!\n");
  if(!first_proc) {
    /* if the process queue is empty,
    either no or one process is running,
    so don't change it */
    return ;
  } else {
    /* there are more processes in the queue.
      suspend the current process,
      queue it,
      make the first in the queue the current one,
      continue it*/
      if(!curr_proc) {
        /* no active process at the moment,
        so no need to stop it */
      } else {
        /* stop the active process and enqueue it */
        kill(curr_proc->pid, SIGSTOP);
        append_proc_queue(curr_proc);
      }
      curr_proc = pop_proc_queue();
      curr_proc->next = NULL;
      kill(curr_proc->pid, SIGCONT); /* continue the process */
  }
}

void sched_init(void) {
  /* initiate process list to be empty */
  curr_proc   = NULL;
  first_proc  = NULL;
  last_proc   = NULL;

  /* register handeler to be called
  whenever a QUANTUM is over */
  signal(SIGALRM, sigalrm_handler);
  ualarm(QUANTUM, QUANTUM);

  }

pid_t sched_create_process(void (*task)(void)) {
  if(!task) {
    fprintf(stderr, "No NULL task allowed!\n");
    exit(-1);
  }

  /* create a new process */
  pid_t pid;
  pid = fork();
  if(pid < 0) {
    fprintf(stderr, "Could not create process!\n");
    exit(-1);
  } else if (pid == 0) {
    /* child process,
    the new process to execute the task
    the alarm interrupt is not enabeled here,
    so don't worry*/

    (*task)();

  } else {
    /* patrent process,
      the process to schedule the processes */

      kill(pid, SIGSTOP); /* suspend the new process */
      proc_t *new_proc = malloc(sizeof(proc_t));
      new_proc->pid = pid;
      append_proc_queue(new_proc);
  }

  return pid;
}
