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
void delay();

// uart.c
void uartinit();
void uartputc(char);
void print_str(char *);
void printint_hex(uint64);
void printint_dec(uint64);

// task.c
void create_task(void *);
void scheduler();
void sched();

// switch.S
void _switch(struct context *, struct context *);

// timer.c
void timerinit();
void timer_handle();

// timervec.S
void timervec();

#endif