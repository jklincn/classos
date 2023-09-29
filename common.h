#ifndef COMMON_H
#define COMMON_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

struct context;
struct task;

// common.c
void delay();
void *memset(void *, int, uint64);

// uart.c
void uartinit();
void uartputc(char);
void print_str(char *);
void printint_hex(uint64);
void printint_dec(uint64);

// task.c
void create_task(void *);
void scheduler();
void switch_to_scheduler();

// switch.S
void _switch(struct context *, struct context *);

// timer.c
void set_next_timer_interrupt();

// trapvec.S
void _trap();
void _restore();

// trap.c
void trapinit();
void trap_handle();

// riscv
uint64 r_mie();
uint64 r_mstatus();
uint64 r_mcause();
uint64 r_mtval();
uint64 r_mepc();
void w_mie(uint64);
void w_mtvec(uint64);
void w_mstatus(uint64);
void enable_timer_interrupt();

#endif