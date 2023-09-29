#include "common.h"

#define MSTATUS_MIE (1L << 3) // machine-mode interrupt enable.
#define MIE_MTIE (1L << 7)    // Machine timer interrupt

void w_mtvec(uint64 x) { asm volatile("csrw mtvec, %0" : : "r"(x)); }

void w_mstatus(uint64 x) { asm volatile("csrw mstatus, %0" : : "r"(x)); }

uint64 r_mstatus() {
  uint64 x;
  asm volatile("csrr %0, mstatus" : "=r"(x));
  return x;
}

void w_mie(uint64 x) { asm volatile("csrw mie, %0" : : "r"(x)); }

uint64 r_mie() {
  uint64 x;
  asm volatile("csrr %0, mie" : "=r"(x));
  return x;
}

uint64 r_mcause() {
  uint64 x;
  asm volatile("csrr %0, mcause" : "=r"(x));
  return x;
}

uint64 r_mtval() {
  uint64 x;
  asm volatile("csrr %0, mtval" : "=r"(x));
  return x;
}

uint64 r_mepc() {
  uint64 x;
  asm volatile("csrr %0, mepc" : "=r"(x));
  return x;
}

void enable_timer_interrupt() { w_mie(r_mie() | MIE_MTIE); }