/**
 * File: scheduler.c
 * Author: Felix Stegmaier
 * Created on: 04.11.2016
 */

#include "../h/scheduler.h"

/**** PRIVATE DECLARATION *****/

proc_t *curr_proc;
queue_t *active_q;
queue_t *paused_q;

int initialized = 0;

void sigalrm_handler(int sig);
void sigchld_handler(int sig);

/******** PUBLIC *********/

void sched_init(void) {
  /* do nothing on multiple calls */
  if(initialized) {
    return;
  }

  /* initiate proces lists to be empty */
  curr_proc = NULL;
  active_q = q_create();
  paused_q = q_create();
  /* register handler to be called when a child process dies */
  signal(SIGCHLD, sigchld_handler);
  /* register handler to be called whenever a QUANTUM is over */
  signal(SIGALRM, sigalrm_handler);
  ualarm(QUANTUM, QUANTUM);
  initialized = 1;
}

pid_t sched_create_process(void (*task)(void)) {
  if(!initialized) {
    return -1;
  }
  if(!task) {
    return 0;
  }

  /* create a new process */
  pid_t pid = fork();
  if(pid < 0) {
    fprintf(stderr, "Could not create process!\n");
    return -2;
  } else if(pid == 0) {
    /* child process */
    (*task)();
    exit(0); /*do not return, as the process is done*/
  } else {
    /* patrent process */
    kill(pid, SIGSTOP); /* suspend the new process */
    /* create handeling node */
    proc_t *new_proc = malloc(sizeof(proc_t));
    new_proc->pid = pid;
    /* enqueue the process to be active */
    q_enqueue(active_q, new_proc);
    return pid;
  }
}

void sched_kill_process(pid_t pid) {
  proc_t* proc;
  if(!initialized) {
    return;
  }
  if(pid <= 0) {
    return;
  }

  if(proc = q_search_and_dequeue(active_q, pid)) {
    free(proc);
    kill(pid, SIGKILL);
  }
  if(proc = q_search_and_dequeue(paused_q, pid)) {
    free(proc);
    kill(pid, SIGKILL);
  }
  if(curr_proc && curr_proc->pid == pid) {
    free(curr_proc);
    curr_proc = NULL;
    kill(pid, SIGKILL);
  }
}


void sched_join_process(pid_t pid) {
  proc_t* proc;
  pid_t p;
  int status;

  if(!initialized) {
    return;
  }
  if(pid <= 0) {
    return;
  }

  if(curr_proc) {
    if(curr_proc->pid != pid
      && !q_contains(active_q, pid)
      && !q_contains(paused_q, pid)) {
        return;
    }
  } else if(!q_contains(active_q, pid)
            && !q_contains(paused_q, pid)) {
    return;
  }



  p = waitpid(pid, &status, 0); /* wait for child to terminate */
  if(p > 0) {
    printf("Child with pid %d finished while joining on it!\n", p);
  }
  if(proc = q_search_and_dequeue(active_q, pid)) {
    free(proc);
  }
  if(proc = q_search_and_dequeue(paused_q, pid)) {
    free(proc);
  }
  if(curr_proc->pid == pid) {
    free(curr_proc);
    curr_proc = NULL;
  }
}


void sched_pause_process(pid_t pid) {
  proc_t* proc;
  if(!initialized) {
    return;
  }
  if(pid <= 0) {
    return;
  }
  if(q_contains(paused_q, pid)) {
    return;
  }

  if(curr_proc
    && curr_proc->pid == pid) {
    kill(pid, SIGSTOP);
    q_enqueue(paused_q, curr_proc);
    curr_proc = NULL;
  }
  if(proc = q_search_and_dequeue(active_q, pid)) {
    kill(pid, SIGSTOP);
    q_enqueue(paused_q, proc);
  }
}


void sched_continue_process(pid_t pid) {
  proc_t* proc;
  if(!initialized) {
    return;
  }
  if(pid <= 0) {
    return;
  }
  if((curr_proc && curr_proc->pid == pid)
    || q_contains(active_q, pid)) {
      return;
  }

  if(proc = q_search_and_dequeue(paused_q, pid)) {
    q_enqueue(active_q, proc);
  }
}


/******** PRIVATE*********/

/**
 * [sigalrm_handler description]
 * @param sig [description]
 */
void sigalrm_handler(int sig) {
  int k;
  printf("Scheduler called by alarm signal!\n");
  if(q_is_empty(active_q)) {
    return;
  }
  if(curr_proc) {
    k = kill(curr_proc->pid, SIGSTOP);
    if(k == -1) {
      fprintf(stderr, "Scheduler: %s\n", strerror(errno));
    }
    q_enqueue(active_q, curr_proc);
  }
  curr_proc = q_dequeue(active_q);
  kill(curr_proc->pid, SIGCONT);
}

/**
 * [sigchld_handler description]
 * @param sig [description]
 */
void sigchld_handler(int sig) {
  /* find out when a child terminates and remove it from the list */
  pid_t p;
  int status;
  proc_t* proc;
  /* non blocking */
  while ((p=waitpid(-1, &status, WNOHANG)) != -1)
  {
    /* Handle the death of pid p */
    if(p == 0) {
      break;
    } else if (p > 0) {
      printf("Child with pid %d finished!\n", p);
      if(curr_proc && curr_proc->pid == p) {
        free(curr_proc);
        curr_proc = NULL;
      }
      if(proc = q_search_and_dequeue(active_q, p)) {
        free(proc);
      }
      if(proc = q_search_and_dequeue(paused_q, p)) {
        free(proc);
      }
    }
  }
}
