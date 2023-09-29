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

void set_next_timer_interrupt() {
  int interval = 1000000; // cycles; about 1/10th second in qemu.
  // set next interrupts
  *(uint64 *)CLINT_MTIMECMP0 = *(uint64 *)CLINT_MTIME + interval;
}