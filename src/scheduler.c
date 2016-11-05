/**
 * File: scheduler.c
 * Author: Felix Stegmaier
 * Created on: 04.11.2016
 */

#include "../h/scheduler.h"

void sched_init(void) {

}

pid_t sched_create_process(void (*task)(void)) {
  return 0;
}

void sched_kill_process(pid_t pid) {

}


void sched_join_process(pid_t pid) {

}


void sched_pause_process(pid_t pid) {

}


void sched_continue_process(pid_t pid) {

}




//
// proc_t *curr_proc;
// proc_t *first_proc;
// proc_t *last_proc;
// proc_t *paused;
//
// proc_t* pop_proc_queue() {
//   if(!first_proc) {
//     /* empty queue */
//     fprintf(stderr,"No member in queue!\n");
//     return NULL;
//   } else if(first_proc == last_proc) {
//     proc_t *temp = first_proc;
//     first_proc = NULL;
//     last_proc = NULL;
//     return temp;
//   } else {
//     proc_t *temp = first_proc;
//     first_proc = first_proc->next;
//     return temp;
//   }
// }
//
// void append_proc_queue(proc_t* proc) {
//   if(!first_proc) {
//     /* empty queue */
//     first_proc = proc;
//     last_proc = proc;
//     last_proc->next = NULL;
//   } else {
//     last_proc->next = proc;
//     last_proc = last_proc->next;
//     last_proc->next = NULL;
//   }
// }
//
// void remove_proc(pid_t pid) {
//
//   proc_t *p;
//   proc_t *last;
//
//   if(curr_proc) {
//     /* see if the process is currenly running */
//     if(curr_proc->pid == pid) {
//       free(curr_proc);
//       curr_proc = NULL;
//     }
//   }
//
//   if(first_proc) {
//     if(first_proc == last_proc) {
//       /* only one element */
//       if(first_proc->pid == pid) {
//         free(first_proc);
//         first_proc = NULL;
//         last_proc = NULL;
//       }
//     } else {
//       /* more than one element */
//       p = first_proc;
//       last = first_proc;
//       while (p) {
//         if(p->pid == pid) {
//           if(p == first_proc) {
//             /* first, but not only element */
//             first_proc = first_proc->next;
//             free(p);
//           } else if(p == last_proc) {
//             /*last, but not only element */
//             last->next = NULL;
//             free(p);
//             break;
//           } else {
//             /* middle, but not only element */
//             last->next = p->next;
//             free(p);
//           }
//         }
//         last = p;
//         p = p->next;
//       }
//     }
//   }
//
//   // also remove from paused
//
//   if(paused) {
//     p = paused;
//     last = paused;
//     while(p) {
//       if(p->pid == pid) {
//         if(p == paused) {
//           /* first, but not only element */
//           paused = paused->next;
//           free(p);
//         } else if(p->next == NULL) {
//           /*last, but not only element */
//           last->next = NULL;
//           free(p);
//           break;
//         } else {
//           /* middle, but not only element */
//           last->next = p->next;
//           free(p);
//         }
//       }
//       last = p;
//       p = p->next;
//     }
//   }
// }
//
// proc_t* retrieve_proc_queue(pid_t pid) {
//   proc_t *p = first_proc;
//   proc_t *last = first_proc;
//   if(first_proc) {
//     if(first_proc == last_proc) {
//       /* only one element */
//       if(first_proc->pid == pid) {
//
//         first_proc = NULL;
//         last_proc = NULL;
//         return p;
//       }
//     } else {
//       /* more than one element */
//       p = first_proc;
//       last = first_proc;
//       while (p) {
//         if(p->pid == pid) {
//           if(p == first_proc) {
//             /* first, but not only element */
//             first_proc = first_proc->next;
//             return p;
//           } else if(p == last_proc) {
//             /*last, but not only element */
//             last->next = NULL;
//             return p;
//             break;
//           } else {
//             /* middle, but not only element */
//             last->next = p->next;
//             return p;
//           }
//         }
//         last = p;
//         p = p->next;
//       }
//     }
//   }
// }
//
//
// void insert_paused(proc_t *p) {
//   if(!p) {
//     return;
//   }
//   if(!paused) {
//     paused = p;
//     p->next = NULL;
//   } else {
//     p->next = paused;
//     paused = p;
//   }
// }
//
// proc_t* retrieve_paused(pid_t pid) {
//   proc_t *p = paused;
//   proc_t *last = paused;
//   while(p) {
//     if(p->pid == pid) {
//       if(p == paused) {
//         /* first, but not only element */
//         paused = paused->next;
//         return p;
//       } else if(p->next == NULL) {
//         /*last, but not only element */
//         last->next = NULL;
//         return p;
//         break;
//       } else {
//         /* middle, but not only element */
//         last->next = p->next;
//         return p;
//       }
//     }
//     last = p;
//     p = p->next;
//   }
// }
//
//
// void sigalrm_handler(int sig) {
//   printf("Scheduler called by interrupt!\n");
//   if(!first_proc) {
//     /* if the process queue is empty,
//     either no or one process is running,
//     so don't change it */
//     return ;
//   } else {
//     /* there are more processes in the queue.
//       suspend the current process,
//       queue it,
//       make the first in the queue the current one,
//       continue it*/
//       if(!curr_proc) {
//         /* no active process at the moment,
//         so no need to stop it */
//       } else {
//         /* stop the active process and enqueue it */
//         int k = kill(curr_proc->pid, SIGSTOP);
//         if(k == -1) {
//           fprintf(stderr, "Scheduler: %s\n", strerror(errno));
//         }
//         append_proc_queue(curr_proc);
//       }
//       curr_proc = pop_proc_queue();
//       curr_proc->next = NULL;
//       kill(curr_proc->pid, SIGCONT); /* continue the process */
//   }
// }
//
// void sigchld_handler(int sig)
// {
//
//     /* find out when a child terminates and remove it from the list */
//     pid_t p;
//     int status;
//     /* non blocking */
//     while ((p=waitpid(-1, &status, WNOHANG)) != -1)
//     {
//        /* Handle the death of pid p */
//        if(p == 0) {
//          break;
//        } else if (p > 0) {
//          printf("Child with pid %d finished!\n", p);
//          remove_proc(p);
//        }
//
//     }
// }
//
// void sched_init(void) {
//   /* initiate process list to be empty */
//   curr_proc   = NULL;
//   first_proc  = NULL;
//   last_proc   = NULL;
//   paused      = NULL;
//
//   /* register handler to be called
//   when a child process dies */
//   signal(SIGCHLD, sigchld_handler);
//
//   /* register handler to be called
//   whenever a QUANTUM is over */
//   signal(SIGALRM, sigalrm_handler);
//   ualarm(QUANTUM, QUANTUM);
//
//   }
//
// pid_t sched_create_process(void (*task)(void)) {
//   if(!task) {
//     fprintf(stderr, "No NULL task allowed!\n");
//     exit(-1);
//   }
//
//   /* create a new process */
//   pid_t pid;
//   pid = fork();
//   if(pid < 0) {
//     fprintf(stderr, "Could not create process!\n");
//     exit(-1);
//   } else if (pid == 0) {
//     /* child process,
//     the new process to execute the task
//     the alarm interrupt is not enabeled here,
//     so don't worry*/
//
//     (*task)();
//     exit(0); /*do not return, as the process is done*/
//   } else {
//     /* patrent process,
//       the process to schedule the processes */
//
//       kill(pid, SIGSTOP); /* suspend the new process */
//       proc_t *new_proc = malloc(sizeof(proc_t));
//       new_proc->pid = pid;
//       append_proc_queue(new_proc);
//       /* process is now enqueued and will be executed */
//   }
//   /* only if in parent */
//   return pid;
// }
//
// void sched_kill_process(pid_t pid) {
//   remove_proc(pid);
//   kill(pid, SIGKILL);
// }
//
// void sched_join_process(pid_t pid) {
//   pid_t p;
//   int status;
//   p = waitpid(pid, &status, 0); /* wait for child to terminate */
//   if(p > 0) {
//     printf("Child with pid %d finished while joining on it!\n", p);
//   }
//   remove_proc(pid);
// }
//
// void sched_pause_process(pid_t pid) {
//   proc_t* p;
//   int k;
//   if(pid>0) {
//     if(curr_proc && curr_proc->pid == pid) {
//       k = kill(curr_proc->pid, SIGSTOP);
//       if(k == -1) {
//         fprintf(stderr, "Scheduler: %s\n", strerror(errno));
//       }
//       p = curr_proc;
//       curr_proc = NULL;
//       insert_paused(p);
//       sigalrm_handler(14);
//     } else {
//       k = kill(curr_proc->pid, SIGSTOP);
//       if(k == -1) {
//         fprintf(stderr, "Scheduler: %s\n", strerror(errno));
//       }
//       p = retrieve_proc_queue(pid);
//       insert_paused(p);
//     }
//
//   }
//
// }
//
// void sched_continue_process(pid_t pid) {
//   proc_t* p;
//   if(pid > 0) {
//     p = retrieve_paused(pid);
//     if(!curr_proc) {
//       curr_proc = p;
//       curr_proc->next = NULL;
//       kill(curr_proc->pid, SIGCONT); /* continue the process */
//     } else {
//       append_proc_queue(p);
//       /* process is now enqueued and will be executed */
//     }
//   }
// }
