#include "common.h"

#define TASKNUMBER 32
#define STACKSIZE 4096 * 2

struct context {
  uint64 ra;
  uint64 sp;
  uint64 s0;
  uint64 s1;
  uint64 s2;
  uint64 s3;
  uint64 s4;
  uint64 s5;
  uint64 s6;
  uint64 s7;
  uint64 s8;
  uint64 s9;
  uint64 s10;
  uint64 s11;
};

enum taskstate { UNUSED, READY, RUNNING };

struct task {
  uint64 pid;
  struct context context;
  enum taskstate state;
};

struct context scheduler_context = {0};
struct task task_list[TASKNUMBER] = {0};
struct task *current = 0;

extern char end[];

uint64 get_new_pid() {
  int i;
  for (i = 0; i < TASKNUMBER; i++) {
    if (task_list[i].state == UNUSED)
      return (uint64)i;
  }
  while (1)
    ;
}

void scheduler() {
  struct task *p;
  while (1)
    for (p = task_list; p < &task_list[TASKNUMBER]; p++) {
      if (p->state == READY) {
        p->state = RUNNING;
        current = p;
        _switch(&scheduler_context, &p->context);
      }
    }
}

void create_task(void *func) {
  struct task new_task = {0};
  uint64 pid = get_new_pid();
  uint64 *stack = (uint64 *)((uint64)end + STACKSIZE * (pid + 1));
  memset(stack - STACKSIZE / sizeof(uint64), 0, STACKSIZE);
  stack -= 32;                  // trapframe
  *stack = (uint64)func;        // mepc
  *(stack + 2) = (uint64)stack; // sp
  // first goto _restore, then mret will goto mepc (i.e func)
  new_task.context.ra = (uint64)_restore;
  new_task.context.sp = (uint64)stack;
  new_task.state = READY;
  new_task.pid = (uint64)pid;
  task_list[pid] = new_task;
}

void switch_to_scheduler() {
  current->state = READY;
  _switch(&current->context, &scheduler_context);
}