#include "common.h"

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
  struct context context;
  enum taskstate state;
};

struct context idle_context = {0};
struct task task_list[64] = {0};
struct task *current = 0;

extern char end[];

void scheduler() {
  struct task *p;
  while (1)
    for (p = task_list; p < &task_list[64]; p++) {
      if (p->state == READY) {
        p->state = RUNNING;
        current = p;
        _switch(&idle_context, &p->context);
      }
    }
}

void sched() { _switch(&current->context, &idle_context); }

void create_task(void *func) {
  int i;
  struct task new_task = {0};
  for (i = 0; i < 64; i++) {
    if (task_list[i].state == UNUSED)
      break;
  }
  if (i >= 64)
    while (1)
      ;
  new_task.context.sp = (uint64)end + 4096 * (i + 1);
  new_task.context.ra = (uint64)func;
  new_task.state = READY;
  memcpy(&task_list[i], &new_task, sizeof(struct task));
}