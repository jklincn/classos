#include "common.h"

__attribute__((aligned(16))) char stack[4096];

void print_task() {
  while (1) {
    print_str("this is task [1]!\n");
    delay();
  }
}

void count_task() {
  static uint64 count = 0;
  while (1) {
    print_str("this is task[2] schedule ");
    printint_dec(++count);
    print_str(" times\n");
    delay();
  }
}

void draw_task() {
  while (1) {
    print_str("**********\n");
    print_str("*        *\n");
    print_str("*        *\n");
    print_str("*        *\n");
    print_str("**********\n");
    delay();
  }
}

void main() {
  uartinit();
  trapinit();
  print_str("Hello, OS!\n");
  create_task(print_task);
  create_task(count_task);
  create_task(draw_task);
  scheduler();
}
