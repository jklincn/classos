#ifndef COMMON_H
#define COMMON_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

struct context;
struct task;

// common.c
void memcpy(void *, const void *, uint64);

// uart.c
void uartinit();
void uartputc(char);
void uartput_uint64(uint64);

// task.c
void create_task(void *);
void scheduler();
void sched();

// switch.S
void _switch(struct context *, struct context *);

#endif