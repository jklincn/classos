/*
    useful website:
    https://starfivetech.com/uploads/sifive-interrupt-cookbook-v1p2.pdf
    https://github.com/five-embeddev/riscv-scratchpad/tree/master/baremetal-startup-c/
*/

#include "common.h"

// core local interruptor (CLINT), which contains the timer.
#define CLINT 0x2000000L
#define CLINT_MTIMECMP0 (CLINT + 0x4000)
#define CLINT_MTIME (CLINT + 0xBFF8) // cycles since boot.

#define MSTATUS_MIE (1L << 3) // machine-mode interrupt enable.
#define MIE_MTIE (1L << 7)    // Machine timer interrupt

static inline void w_mtvec(uint64 x) {
  asm volatile("csrw mtvec, %0" : : "r"(x));
}

static inline void w_mstatus(uint64 x) {
  asm volatile("csrw mstatus, %0" : : "r"(x));
}

static inline uint64 r_mstatus() {
  uint64 x;
  asm volatile("csrr %0, mstatus" : "=r"(x));
  return x;
}

static inline void w_mie(uint64 x) { asm volatile("csrw mie, %0" : : "r"(x)); }

static inline uint64 r_mie() {
  uint64 x;
  asm volatile("csrr %0, mie" : "=r"(x));
  return x;
}

// trap_context[0]: save/restore a1
// trap_context[1]: save/restore a2
// trap_context[2]: save/restore a3
// trap_context[3]: save/restore ra
// trap_context[4]: address of CLINT MTIMECMP register
// trap_context[5]: desired interval (in cycles) between timer interrupts
uint64 trap_context[6];

void timerinit() {
  int interval = 1000000; // cycles; about 1/10th second in qemu.

  // set next interrupts
  *(uint64 *)CLINT_MTIMECMP0 = *(uint64 *)CLINT_MTIME + interval;

  trap_context[4] = CLINT_MTIMECMP0;
  trap_context[5] = interval;

  // set the machine-mode trap handler.
  w_mtvec((uint64)timervec);

  // enable machine-mode interrupts.
  w_mstatus(r_mstatus() | MSTATUS_MIE);

  // enable machine-mode timer interrupts.
  w_mie(r_mie() | MIE_MTIE);
}

void timer_handle() { print_str("timer interrupt!\n"); }