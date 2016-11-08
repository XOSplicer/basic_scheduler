/**
 * File: queue.c
 * Author: Felix Stegmaier
 * Created on: 04.11.2016
 */

#include "../h/queue.h"

/**** PRIVATE DECLARATION *****/


/******** PUBLIC *********/

queue_t* q_create() {
  queue_t* q = malloc(sizeof(queue_t));
  q->first = NULL;
  q->last = NULL;
  return q;
}

int q_is_empty(queue_t* q) {
  if(!q) {
    return -1;
  }

  if(q->first) {
    return 0;
  } else {
    return 1;
  }
}

void q_enqueue(queue_t* q, proc_t *proc) {
  if(!q || !proc) {
    return;
  }

  if(!q->first) {
    q->first = proc;
    q->last = proc;
    proc->next = NULL;
  } else {
    q->last->next = proc;
    q->last = proc;
    proc->next = NULL;
  }
}

proc_t* q_dequeue(queue_t* q) {
  proc_t* proc;
  if(!q) {
    return NULL;
  }
  if(!q->first) {
    return NULL;
  }

  if(q->first == q->last) {
    proc = q->first;
    q->first = NULL;
    q->last = NULL;
    proc->next = NULL;
    return proc;
  } else {
    proc = q->first;
    q->first = q->first->next;
    proc->next = NULL;
    return proc;
  }
}

proc_t* q_search_and_dequeue(queue_t* q, pid_t pid) {
  proc_t* proc;
  proc_t* prior;
  if(!q) {
    return NULL;
  }
  if(!q->first) {
    return NULL;
  }

  if(q->first == q->last
    && q->first->pid == pid) {
    proc = q->first;
    q->first = NULL;
    q->last = NULL;
    proc->next = NULL;
    return proc;
  }

  proc = q->first;
  prior = proc;
  while(proc) {
    if(proc->pid == pid) {
      if(proc = q->first) {
        q->first = proc->next;
        proc->next = NULL;
        return proc;
      } else if(proc = q->last) {
        q->last = prior;
        prior->next = NULL;
        proc->next = NULL;
        return proc;
      } else {
        prior->next = proc->next;
        proc->next = NULL;
        return proc;
      }
    }
    prior = proc;
    proc = proc->next;
  }
  return NULL;
}

int q_contains(queue_t* q, pid_t pid) {
  proc_t* proc;
  if(!q) {
    return 0;
  }
  if(!q->first) {
    return 0;
  }

  proc = q->first;
  while(proc) {
    if(proc->pid == pid) {
      return 0;
    }
    proc = proc->next;
  }
  return 0;
}


/******** PRIVATE *********/
